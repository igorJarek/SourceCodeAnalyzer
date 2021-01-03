#include "MainWindow.h"

#include "CodeRenderWindow.h"
#include "AnalyzeWindow.h"
#include "CreateDatabaseWindow.h"

#include <QFileDialog>
#include <QTextEdit>
#include <QTextStream>
#include <QMessageBox>
#include <QProgressBar>

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

    m_ui.splitter->setSizes({300, 400});
}

void MainWindow::initSignalsConnections()
{
    // Window Menu Actions
    connect(m_ui.actionCreate_Database,  SIGNAL(triggered()),                        this, SLOT(create_database()));
    connect(m_ui.actionOpen_Database,    SIGNAL(triggered()),                        this, SLOT(open_database()));
    connect(m_ui.actionSave_As_Database, SIGNAL(triggered()),                        this, SLOT(save_as_database()));
    connect(m_ui.actionSave_Database,    SIGNAL(triggered()),                        this, SLOT(save_database()));
    connect(m_ui.actionExit,             SIGNAL(triggered()),                        this, SLOT(exit()));

    // Other Actions
    connect(m_ui.actionCreateView,       SIGNAL(triggered()),                               this, SLOT(create_view()));
    connect(m_ui.viewsTab,               SIGNAL(tabCloseRequested(int)),                    this, SLOT(filesTab_closeTab(int)));
    connect(m_ui.databaseTree,           SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(databaseTree_contextMenu(const QPoint&)));
}

void MainWindow::fillDatabaseTree()
{
    if(!m_app.getDatabase())
        QMessageBox::critical(this, "Database Error", "First create database");
    else
        m_ui.databaseTree->clear();

    QSharedPointer<Database> databasePtr = m_app.getDatabase();

    QueryResults fileList;
    DatabaseQueryErrMsg queryErrMsg = databasePtr->recvQuery
    (
        "SELECT * FROM [..\\file_list]",
        fileList
    );
    if(databasePtr->isNotOK())
    {
        QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
        return;
    }

    for(std::vector<std::string>& fileRow : fileList.rows)
    {
        const std::string& filePath = fileRow[1];

        QTreeWidgetItem* fileRootItem = new QTreeWidgetItem(m_ui.databaseTree);
        fileRootItem->setText(0, QString::fromStdString(filePath.substr(m_app.getAnalizedFolderPath().size())));
        fileRootItem->setText(1, "");
        fileRootItem->setText(2, "");

        QueryResults fileFunctions;
        queryErrMsg = databasePtr->recvQuery
        (
            "SELECT FunctionsNameTokenID FROM [" + filePath + "\\functions]",
            fileFunctions
        );
        if(databasePtr->isNotOK())
        {
            QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
            return;
        }

        for(std::vector<std::string>& fileFunction : fileFunctions.rows)
        {
            QueryResults functionToken;
            queryErrMsg = databasePtr->recvQuery
            (
                "SELECT TokenSpelling, TokenStartPos_Line "
                "FROM [" + filePath + "\\tokens] "
                "WHERE TokenID = " + fileFunction[0],
                functionToken
            );
            if(databasePtr->isNotOK())
            {
                QMessageBox::critical(nullptr, "Query Error", QString(queryErrMsg), QMessageBox::StandardButton::Ok);
           
            }

            std::vector<std::string>& fileFunctionToken = functionToken.rows.front();
            QTreeWidgetItem* item = new QTreeWidgetItem(fileRootItem);
            item->setText(0, "");
            item->setText(1, QString::fromStdString(fileFunctionToken[0]));
            item->setText(2, QString::fromStdString(fileFunctionToken[1]));
        }
    }
}

void MainWindow::create_database()
{
    CreateDatabaseWindow createDatabaseWindow(m_app, this);
    createDatabaseWindow.setModal(true);
    if(createDatabaseWindow.exec())
        fillDatabaseTree();
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
    QString filter = tr("SQLite File (*.sqlite3)");
    QString filePath = QFileDialog::getSaveFileName(this, tr("Database Path"), QString(), tr("SQLite File (*.sqlite3)"), &filter);

    if(!filePath.isEmpty())
    {
        if(m_app.getDatabase())
        {
            Database& database = *m_app.getDatabase();

            QProgressBar progressBar(this);
            progressBar.setMinimum(0);
            progressBar.setMaximum(100);
            progressBar.setValue(0);
            progressBar.show();

            database.saveAsDatabase
            (
                filePath.toStdString(),
                [&progressBar](double currentPercent) -> void
                {
                    progressBar.setValue(currentPercent);
                }
            );
        }
    }
}

void MainWindow::save_database()
{

}

void MainWindow::exit()
{
    close();
}

void MainWindow::create_view()
{
    const QStringList& args = m_ui.actionCreateView->data().toStringList();

    QSharedPointer<Database> database = m_app.getDatabase();

    if(database)
    {
        if(database->isOK())
        {
            AnalyzeWindow analyzeWindow(m_app, args, this);
            analyzeWindow.setModal(true);
            if(analyzeWindow.exec())
            {
                QTabWidget* viewsTab = m_ui.viewsTab;
                CodeRenderWindow* render = new CodeRenderWindow(m_app, this);
                int tabIndex = viewsTab->addTab(render, QString("Renderer"));
                viewsTab->setCurrentIndex(tabIndex);
            }
            else
                QMessageBox::warning(this, "Analizing Failed", "Something went wrong...", QMessageBox::StandardButton::Ok);
        }
        else
            QMessageBox::warning(this, "Analizing Failed", "Database has errors...", QMessageBox::StandardButton::Ok);
    }
    else
        QMessageBox::warning(this, "Analizing Failed", "Please open or create database first", QMessageBox::StandardButton::Ok);
}

void MainWindow::filesTab_closeTab(int index)
{
    QTabWidget* viewsTab = m_ui.viewsTab;

    QWidget* deletedTabs = viewsTab->widget(index);
    viewsTab->removeTab(index);

    delete deletedTabs;
}

void MainWindow::databaseTree_contextMenu(const QPoint& point)
{
    QTreeWidgetItem* clickedItem       = m_ui.databaseTree->itemAt(point);
    QTreeWidgetItem* clickedParentItem = clickedItem->parent();

    if(clickedItem)
    if(clickedItem->text(0).isEmpty())
    {
        QStringList args;
        args.append(m_app.getAnalizedFolderPath() + clickedParentItem->text(0));
        args.append(clickedItem->text(1));
        args.append(clickedItem->text(2));

        m_ui.actionCreateView->setData(QVariant(args));

        QMenu menu(this);
        menu.addAction(m_ui.actionCreateView);

        menu.exec(m_ui.databaseTree->mapToGlobal(point));
    }
}
