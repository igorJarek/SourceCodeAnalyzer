#include "MainWindow.h"

#include "CodeRenderWindow.h"
#include "AnalyzeWindow.h"
#include "CreateDatabaseWindow.h"

#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(App& app, QWidget *parent) : 
    QMainWindow(parent),
    m_app(app)
{
    initUi();
    initSignalsConnections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initUi()
{
    m_ui.setupUi(this);

    m_ui.splitter->setSizes({200, 400});
}

void MainWindow::initSignalsConnections()
{
    // Window Menu Actions
    connect(m_ui.actionCreate_Database,  SIGNAL(triggered()),                        this, SLOT(create_database()));
    connect(m_ui.actionOpen_Database,    SIGNAL(triggered()),                        this, SLOT(open_database()));
    connect(m_ui.actionSave_As_Database, SIGNAL(triggered()),                        this, SLOT(save_as_database()));
    connect(m_ui.actionSave_Database,    SIGNAL(triggered()),                        this, SLOT(save_database()));
    connect(m_ui.actionStart_Analyze,    SIGNAL(triggered()),                        this, SLOT(start_analyze()));
    connect(m_ui.actionExit,             SIGNAL(triggered()),                        this, SLOT(exit()));

    // Other Actions
    connect(m_ui.filesTree,             SIGNAL(doubleClicked(const QModelIndex&)),  this, SLOT(filesTree_doubleClick(const QModelIndex &)));
    connect(m_ui.filesTab,              SIGNAL(tabCloseRequested(int)),             this, SLOT(filesTab_closeTab(int)));
}

void MainWindow::create_database()
{
    CreateDatabaseWindow createDatabaseWindow(m_app, this);
    createDatabaseWindow.setModal(true);
    if(createDatabaseWindow.exec())
    {
        QModelIndex index = model.setRootPath(m_app.getAnalizedFolderPath());

        m_ui.filesTree->setModel(&model);
        m_ui.filesTree->setRootIndex(index);
        m_ui.filesTree->hideColumn(2);
        m_ui.filesTree->hideColumn(3);
    }
}

void MainWindow::open_database()
{
    QString filter = tr("SQLite File (*.sqlite3)");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Database Path"), QString(), tr("SQLite File (*.sqlite3)"), &filter);

    if(!filePath.isEmpty())
    {
        if(m_app.getDatabase())
        {
            int32_t ret = QMessageBox::question(this, "Database Exists", "Do you want replace existed database ?", QMessageBox::StandardButton::Yes, QMessageBox::StandardButton::No);
            if(ret == QMessageBox::StandardButton::Yes)
                m_app.reallocateDatabase(filePath);
            else
                return;
        }
        else
            m_app.allocateDatabase(filePath);

        Database& database = *m_app.getDatabase();

        database.openDatabase(DatabaseOptions::READ_WRITE_DB_FILE |
                              DatabaseOptions::FILE_DB_FILE
                              );

        if(database.isNotOK())
            QMessageBox::warning(this, "Database Error", database.lastErrorMsg().c_str(), QMessageBox::StandardButton::Ok, QMessageBox::StandardButton::Cancel);
        else
        {
            m_app.setDatabasePath(filePath);
            QString newWindowTitle = windowTitle();
            newWindowTitle += " - " + filePath;
            setWindowTitle(newWindowTitle);
        }
    }
}

void MainWindow::save_as_database()
{

}

void MainWindow::save_database()
{

}

void MainWindow::start_analyze()
{

}

void MainWindow::exit()
{
    close();
}

void MainWindow::filesTree_doubleClick(const QModelIndex& modelIndex)
{
    QTabWidget* filesTab = m_ui.filesTab;
    QString absoluteFilePath = model.filePath(modelIndex);

    QFile file(absoluteFilePath);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QStringList absoluteFilePathSplitted = absoluteFilePath.split("/");

            // QTextDocument zamiast QTextEdit
            QTextEdit* textEdit = new QTextEdit();
            int index = filesTab->addTab(textEdit, absoluteFilePathSplitted.last());

            filesTab->setCurrentIndex(index);

            QTextStream stream(&file);
            QString line;

            while(!stream.atEnd())
            {
                line = stream.readLine();
                textEdit->append(line);
            }

            file.close();
        }
    }
}

void MainWindow::filesTab_closeTab(int index)
{
    QTabWidget* filesTab = m_ui.filesTab;

    QWidget* deletedTabs = filesTab->widget(index);
    filesTab->removeTab(index);

    delete deletedTabs;
}