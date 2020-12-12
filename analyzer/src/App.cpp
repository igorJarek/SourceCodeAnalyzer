#include "App.h"

App::App(int argc, char *argv[]) :
    QApplication(argc, argv)
{
    
}

App::~App()
{
    
}

void App::reallocateDatabase(const QString& databasePath)
{
    if(m_database)
        m_database.clear();

    allocateDatabase(databasePath);
}

void App::allocateDatabase(const QString& databasePath)
{
     m_database = QSharedPointer<Database>(new Database(databasePath.toStdString()));
}

void App::buildSourceCodeBlocks()
{
    
}