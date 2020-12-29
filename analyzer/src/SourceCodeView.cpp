#include "SourceCodeView.h"
#include <Database/Database.h>

#include <QMessageBox>
#include <string>

SourceCodeView::SourceCodeView(const QSharedPointer<Database>& database, const QString& mainFilePath, const QString& mainFunctionName, int32_t mainFunctionLine) :
    m_database(database),
    m_mainFilePath(mainFilePath),
    m_mainFunctionName(mainFunctionName),
    m_mainFunctionLine(mainFunctionLine)
{
    
}

SourceCodeView::~SourceCodeView()
{
    
}

void SourceCodeView::build(std::function<void (void)> stateStatus)
{
    findAndProcessMainFunction(stateStatus);
    iteratesCallsQueue(stateStatus);
}

void SourceCodeView::findAndProcessMainFunction(std::function<void (void)> stateStatus)
{
    QueryResults mainFunctionNameToken;
    DatabaseQueryErrMsg queryErrMsg = m_database->recvQuery
    (
        "SELECT TokenID "
        "FROM [" + m_mainFilePath.toStdString() + "\\tokens] "
        "WHERE TokenSpelling = '" + m_mainFunctionName.toStdString() + "' AND TokenStartPos_Line = " + std::to_string(m_mainFunctionLine), 
        mainFunctionNameToken
    );
    if(m_database->isNotOK())
    {
        QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
        return;
    }

    if(mainFunctionNameToken.rows.front().empty())
    {
        QMessageBox::critical(nullptr, "Error", "Main Function hasn't found", QMessageBox::StandardButton::Ok);
        return;
    }

    uint32_t mainFunctionNameTokenID = std::stoi(mainFunctionNameToken.rows.front().at(0));

    QueryResults mainFileFunctions;
    queryErrMsg = m_database->recvQuery
    (
        "SELECT * "
        "FROM [" + m_mainFilePath.toStdString() + "\\functions] "
        "WHERE FunctionsNameTokenID = " + std::to_string(mainFunctionNameTokenID),
        mainFileFunctions
    );
    if(m_database->isNotOK())
    {
        QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
        return;
    }

    const std::vector<std::string>& mainFunctionDefRow = mainFileFunctions.rows.front();
    if(mainFunctionDefRow.empty())
    {
        QMessageBox::critical(nullptr, "Main Function Error", "Main Function must be function definition", QMessageBox::StandardButton::Ok);
        return;
    }

    uint32_t openingDefTokenID = std::stoll(mainFunctionDefRow[2]);
    uint32_t closingDefTokenID = std::stoll(mainFunctionDefRow[3]);

    std::string openingDefTokenIDStr = std::to_string(openingDefTokenID);
    std::string closingDefTokenIDStr = std::to_string(closingDefTokenID);

    QueryResults mainFileTokens;
    queryErrMsg = m_database->recvQuery
    (
        "SELECT * "
        "FROM [" + m_mainFilePath.toStdString() + "\\tokens] "
        "WHERE TokenID BETWEEN " + openingDefTokenIDStr + " AND " + closingDefTokenIDStr,
        mainFileTokens
    );
    if(m_database->isNotOK())
    {
        QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
        return;
    }

    QueryResults mainFunctionCallings;
    queryErrMsg = m_database->recvQuery
    (
        "SELECT * "
        "FROM [" + m_mainFilePath.toStdString() + "\\calling] "
        "WHERE CallingNameTokenID BETWEEN " + openingDefTokenIDStr + " AND " + closingDefTokenIDStr,
        mainFunctionCallings
    );
    if(m_database->isNotOK())
    {
        QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
        return;
    }

    for(std::vector<std::string>& callingRow : mainFunctionCallings.rows)
    {
        SourceCodeViewCalling sourceCodeViewCalling;
        sourceCodeViewCalling.filePath   = callingRow[2];
        sourceCodeViewCalling.functionID = std::stoll(callingRow[3]);

        m_functionCallsQueue.enqueue(sourceCodeViewCalling);
    }

    SourceCodeBlockPtr sourceCodeBlock = SourceCodeBlockPtr(new SourceCodeBlock(mainFileTokens, mainFunctionCallings));

    SourceCodeBlockVecPtr sourceCodeBlockVecPtr = SourceCodeBlockVecPtr(new QVector<QSharedPointer<SourceCodeBlock>>);
    sourceCodeBlockVecPtr->append(sourceCodeBlock);

    m_functionSourceCodeBlockVec.append(sourceCodeBlockVecPtr);
}

void SourceCodeView::iteratesCallsQueue(std::function<void (void)> stateStatus)
{
    do
    {
        int32_t stageSize = m_functionCallsQueue.size();
        if(stageSize)
        {
            SourceCodeBlockVecPtr sourceCodeBlockVecPtr = SourceCodeBlockVecPtr(new QVector<QSharedPointer<SourceCodeBlock>>);
            m_functionSourceCodeBlockVec.append(sourceCodeBlockVecPtr);
        }

        SourceCodeViewCalling sourceCodeViewCalling;
        for(int32_t i = 0; i < stageSize; ++i)
        {
            sourceCodeViewCalling = m_functionCallsQueue.dequeue();

            QueryResults fileFunctionDef;
            DatabaseQueryErrMsg queryErrMsg = m_database->recvQuery
            (
                "SELECT * "
                "FROM [" + sourceCodeViewCalling.filePath + "\\functions] "
                "WHERE FunctionsID = " + std::to_string(sourceCodeViewCalling.functionID),
                fileFunctionDef
            );
            if(m_database->isNotOK())
            {
                QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
                return;
            }

            const std::vector<std::string>& fileFunctionDefRow = fileFunctionDef.rows.front();
            uint32_t openingDefTokenID      = std::stoll(fileFunctionDefRow[2]);
            uint32_t closingDefTokenID      = std::stoll(fileFunctionDefRow[3]);

            std::string openingDefTokenIDStr = std::to_string(openingDefTokenID);
            std::string closingDefTokenIDStr = std::to_string(closingDefTokenID);

            QueryResults functionsTokens;
            queryErrMsg = m_database->recvQuery
            (
                "SELECT * "
                "FROM [" + sourceCodeViewCalling.filePath + "\\tokens] "
                "WHERE TokenID BETWEEN " + openingDefTokenIDStr + " AND " + closingDefTokenIDStr,
                functionsTokens
            );
            if(m_database->isNotOK())
            {
                QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
                return;
            }

            QueryResults functionCallings;
            queryErrMsg = m_database->recvQuery
            (
                "SELECT * "
                "FROM [" + sourceCodeViewCalling.filePath + "\\calling] "
                "WHERE CallingNameTokenID BETWEEN " + openingDefTokenIDStr + " AND " + closingDefTokenIDStr,
                functionCallings
            );
            if(m_database->isNotOK())
            {
                QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
                return;
            }

            for(std::vector<std::string>& callingRow : functionCallings.rows)
            {
                SourceCodeViewCalling sourceCodeViewCalling;
                sourceCodeViewCalling.filePath   = callingRow[2];
                sourceCodeViewCalling.functionID = std::stoll(callingRow[3]);

                m_functionCallsQueue.enqueue(sourceCodeViewCalling);
            }

            SourceCodeBlockPtr sourceCodeBlock = SourceCodeBlockPtr(new SourceCodeBlock(functionsTokens, functionCallings));

            m_functionSourceCodeBlockVec.last()->append(sourceCodeBlock);
        }

    }while(!m_functionCallsQueue.empty());
}
