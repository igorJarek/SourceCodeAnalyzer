#include "App.h"

#include <QFontDatabase>
#include <QMessageBox>
#include <vector>

App::App(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    int id = QFontDatabase::addApplicationFont("fonts/JetBrainsMono-Regular.ttf");
    if(id == -1)
        QMessageBox::critical(nullptr, "Font Load Failed", "Couldn't load JetBrainsMono-Regular.ttf font.", QMessageBox::StandardButton::Ok);
}

App::~App()
{
    
}

void App::reallocateDatabase()
{
    if(m_database)
        m_database.clear();

    allocateDatabase();
}

void App::reallocateDatabase(const QString& databasePath)
{
    if(m_database)
        m_database.clear();

    allocateDatabase(databasePath);
}

void App::allocateDatabase()
{
     m_database = QSharedPointer<Database>(new Database);
}

void App::allocateDatabase(const QString& databasePath)
{
     m_database = QSharedPointer<Database>(new Database(databasePath.toStdString()));
}

void App::buildSourceCodeBlocks()
{
    if(m_database)
    if(m_database->isOK())
    {
        QueryResults fileListResults;
        DatabaseQueryErrMsg queryErrMsg = m_database->recvQuery("SELECT * FROM [..\\file_list]", fileListResults);
        if(m_database->isNotOK())
        {
            QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
            return;
        }
        else
        {
            uint32_t fileListIndex = 0;
            m_sourceCodeBlocks.resize(fileListResults.rows.size());

            for(std::vector<std::string>& row : fileListResults.rows)
            {
                std::string& fileNameStr = row[1];
                std::string tokenTable = fileNameStr + "\\tokens";

                QueryResults tokensResults;
                queryErrMsg = m_database->recvQuery("SELECT * FROM [" + tokenTable + "]", tokensResults);
                if(m_database->isNotOK())
                {
                    QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
                    m_sourceCodeBlocks.clear();
                    return;
                }
                else
                {
                    QueryResults lineCountResults;
                    queryErrMsg = m_database->recvQuery("SELECT max(TokenEndPos_Line) FROM [" + tokenTable + "]", lineCountResults);
                    if(m_database->isNotOK())
                    {
                        QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
                        m_sourceCodeBlocks.clear();
                        return;
                    }
                    else
                    {
                        int32_t lineCount = std::stoi(lineCountResults.rows.front().front());

                        QSharedPointer<SourceCodeBlock> sourceCodeBlock = QSharedPointer<SourceCodeBlock>(new SourceCodeBlock(tokensResults, lineCount));

                        m_sourceCodeBlocks[fileListIndex++] = sourceCodeBlock;
                    }
                }
            }
        }
    }
}
