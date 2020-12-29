#include "App.h"

#include <QFontDatabase>
#include <QMessageBox>

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

void App::addSourceCodeView(const QSharedPointer<SourceCodeView>& sourceCodeView)
{
    m_sourceCodeViews.append(sourceCodeView);
}
