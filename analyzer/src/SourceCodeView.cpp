#include "SourceCodeView.h"
#include "Database/Database.h"

#include <QtSvg/QSvgGenerator>
#include <QMessageBox>
#include <string>

SourceCodeView::SourceCodeView(const QSharedPointer<Database>& database, const QString& viewName, const QString& mainFilePath, const QString& analyzedFolder, 
                               const QString& mainFunctionName, int32_t mainFunctionLine) :
    m_database(database),
    m_viewName(viewName),
    m_mainFilePath(mainFilePath),
    m_analyzedFolder(analyzedFolder),
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
    setSourceCodeBlocksAlignment();
    generateConnectionLines();
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

    QString subStrMainFilePath = m_mainFilePath;
    SourceCodeBlockPtr sourceCodeBlock = SourceCodeBlockPtr(new SourceCodeBlock(subStrMainFilePath.remove(0, m_analyzedFolder.size()), mainFileTokens, mainFunctionCallings));

    SourceCodeBlockVecPtr sourceCodeBlockVecPtr = SourceCodeBlockVecPtr(new QVector<QSharedPointer<SourceCodeBlock>>);
    sourceCodeBlockVecPtr->append(sourceCodeBlock);

    m_functionSourceCodeBlockVec.append(sourceCodeBlockVecPtr);

    for(std::vector<std::string>& callingRow : mainFunctionCallings.rows)
    {
        SourceCodeViewCalling sourceCodeViewCalling;
        sourceCodeViewCalling.filePath   = callingRow[2];
        sourceCodeViewCalling.functionID = std::stoll(callingRow[3]);
        sourceCodeViewCalling.caller     = sourceCodeBlock;

        m_functionCallsQueue.enqueue(sourceCodeViewCalling);
    }
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

        SourceCodeViewCalling sourceCodeViewCallingQueue;
        for(int32_t i = 0; i < stageSize; ++i)
        {
            sourceCodeViewCallingQueue = m_functionCallsQueue.dequeue();

            QueryResults fileFunctionDef;
            DatabaseQueryErrMsg queryErrMsg = m_database->recvQuery
            (
                "SELECT * "
                "FROM [" + sourceCodeViewCallingQueue.filePath + "\\functions] "
                "WHERE FunctionsID = " + std::to_string(sourceCodeViewCallingQueue.functionID),
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
                "FROM [" + sourceCodeViewCallingQueue.filePath + "\\tokens] "
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
                "FROM [" + sourceCodeViewCallingQueue.filePath + "\\calling] "
                "WHERE CallingNameTokenID BETWEEN " + openingDefTokenIDStr + " AND " + closingDefTokenIDStr,
                functionCallings
            );
            if(m_database->isNotOK())
            {
                QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
                return;
            }

            QString subStrMainFilePath = QString::fromStdString(sourceCodeViewCallingQueue.filePath); 
            SourceCodeBlockPtr sourceCodeBlock = SourceCodeBlockPtr(new SourceCodeBlock(subStrMainFilePath.remove(0, m_analyzedFolder.size()), functionsTokens, functionCallings));
            sourceCodeViewCallingQueue.caller->addDefinitions(sourceCodeBlock);
            m_functionSourceCodeBlockVec.last()->append(sourceCodeBlock);

            for(std::vector<std::string>& callingRow : functionCallings.rows)
            {
                SourceCodeViewCalling sourceCodeViewCalling;
                sourceCodeViewCalling.filePath   = callingRow[2];
                sourceCodeViewCalling.functionID = std::stoll(callingRow[3]);
                sourceCodeViewCalling.caller     = sourceCodeBlock;

                m_functionCallsQueue.enqueue(sourceCodeViewCalling);
            }
        }

    }while(!m_functionCallsQueue.empty());
}

void SourceCodeView::setSourceCodeBlocksAlignment()
{
    const uint16_t STAGE_X_GAP {100};
    const uint16_t STAGE_Y_GAP {20};

    // get stages info (max height stage, stages width and height)
    uint64_t maxHeightStage {0};
    QVector<QPoint> stagesInfo(m_functionSourceCodeBlockVec.size());

    for(size_t stageListIndex {0}; stageListIndex < m_functionSourceCodeBlockVec.size(); ++stageListIndex)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = m_functionSourceCodeBlockVec[stageListIndex];
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            const SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->at(j);
            QPoint sourceCodeBlockSize = sourceCodeBlockPtr->getSize();

            stagesInfo[stageListIndex].setY( stagesInfo[stageListIndex].y() + sourceCodeBlockSize.y() + STAGE_Y_GAP);
            if(sourceCodeBlockSize.x() > stagesInfo[stageListIndex].x())
                stagesInfo[stageListIndex].setX(sourceCodeBlockSize.x());
        }

        stagesInfo[stageListIndex].setY( stagesInfo[stageListIndex].y() - STAGE_Y_GAP);

        if(stagesInfo[stageListIndex].y() > maxHeightStage)
            maxHeightStage = stagesInfo[stageListIndex].y();
    }

    // set initial positions
    uint64_t xPosition {0};
    for(size_t stageListIndex {0}; stageListIndex < m_functionSourceCodeBlockVec.size(); ++stageListIndex)
    {
        SourceCodeView::SourceCodeBlockVecPtr& vecPtr = m_functionSourceCodeBlockVec[stageListIndex];

        uint64_t yPosition = (maxHeightStage - stagesInfo[stageListIndex].y()) / 2;
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->operator[](j);

            sourceCodeBlockPtr->setWidth(stagesInfo[stageListIndex].x());
            sourceCodeBlockPtr->setPosition(xPosition, yPosition);
            yPosition += sourceCodeBlockPtr->getSize().y() + STAGE_Y_GAP;
        }

        xPosition += stagesInfo[stageListIndex].x() + STAGE_X_GAP;
    }

    m_size.setWidth(xPosition - STAGE_X_GAP);
    m_size.setHeight(maxHeightStage);
}

void SourceCodeView::generateConnectionLines()
{
    for(size_t stageListIndex {0}; stageListIndex < m_functionSourceCodeBlockVec.size(); ++stageListIndex)
    {
        SourceCodeView::SourceCodeBlockVecPtr& vecPtr = m_functionSourceCodeBlockVec[stageListIndex];

        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->operator[](j);

            QVector<QPoint>& callingFirstPosVec = sourceCodeBlockPtr->getCallingFirstPos();
            QPoint sourceCodeBlockSize = sourceCodeBlockPtr->getSize();
            QPoint sourceCodeBlockPos  = sourceCodeBlockPtr->getPosition();

            for(uint32_t callingIndex = 0; callingIndex < callingFirstPosVec.size(); ++callingIndex)
            {
                QPoint callingPos = callingFirstPosVec[callingIndex];
                SourceCodeViewLinesPtr sourceCodeViewLinesPtr = QSharedPointer<SourceCodeViewLines>(new SourceCodeViewLines);

                QSharedPointer<SourceCodeBlock> ithDefinition = sourceCodeBlockPtr->getIthDefinition(callingIndex);
                QPoint ithDefBlockSize = ithDefinition->getSize();
                QPoint ithDefBlockPos  = ithDefinition->getPosition();

                sourceCodeViewLinesPtr->firstLine.setLine(sourceCodeBlockPos.x() + callingPos.x(),
                                                          sourceCodeBlockPos.y() + callingPos.y(),
                                                          sourceCodeBlockPos.x() + sourceCodeBlockSize.x(),
                                                          sourceCodeBlockPos.y() + callingPos.y());

                sourceCodeViewLinesPtr->secondLine.setLine(sourceCodeBlockPos.x() + sourceCodeBlockSize.x(),
                                                           sourceCodeBlockPos.y() + callingPos.y(),
                                                           ithDefBlockPos.x(),
                                                           ithDefBlockPos.y() + ithDefBlockSize.y() / 2);

                m_lines.append(sourceCodeViewLinesPtr);
            }
        }
    }
}

void SourceCodeView::draw(QPainter& painter, double zoom)
{
    painter.scale(zoom, zoom);

    for(const SourceCodeBlockVecPtr& sourceCodeBlockVec : m_functionSourceCodeBlockVec)
    {
        for(const SourceCodeBlockPtr& sourceCodeBlockPtr : *sourceCodeBlockVec)
        {
            painter.translate(sourceCodeBlockPtr->getPosition().x(), sourceCodeBlockPtr->getPosition().y());
            sourceCodeBlockPtr->draw(painter);
            painter.translate(-sourceCodeBlockPtr->getPosition().x(), -sourceCodeBlockPtr->getPosition().y());
        }
    }

    QPen pen(QColor(80, 200, 175));

    if(zoom < 1.0)
        pen.setWidth(2);
    else
        pen.setWidth(1);

    for(const SourceCodeViewLinesPtr& sourceCodeViewLines : m_lines)
    {
        painter.setPen(pen);
        painter.drawLine(sourceCodeViewLines->firstLine);
        painter.drawLine(sourceCodeViewLines->secondLine);
    }
}

void SourceCodeView::saveToSVG(const QString& filePath)
{
    QSvgGenerator generator;
    generator.setFileName(filePath + '/' + m_viewName + ".svg");
    generator.setSize(m_size);
    generator.setViewBox(QRect(0, 0, m_size.width(), m_size.height()));
    generator.setTitle(m_viewName);
    generator.setDescription("An SVG drawing created by the SVG Generator Example provided with Qt.");
    
    QPainter painter(&generator);

    painter.fillRect(QRect(0, 0, m_size.width(), m_size.height()), QColor(30, 30, 30));

    draw(painter, 1.0);

    painter.end();
}
