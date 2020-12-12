#include "MainWindow.h"

#include <QFileDialog.h>
#include <QTextEdit.h>
#include <QTextStream.h>

#include <CodeRenderWindow.h>

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
    connect(m_ui.actionStart_Analyze,   SIGNAL(triggered()),                        this, SLOT(start_analyze()));
    connect(m_ui.filesTree,             SIGNAL(doubleClicked(const QModelIndex&)),  this, SLOT(filesTree_doubleClick(const QModelIndex &)));
    connect(m_ui.filesTab,              SIGNAL(tabCloseRequested(int)),             this, SLOT(filesTab_closeTab(int)));
}

void MainWindow::start_analyze()
{
    m_analyzeWindow = new AnalyzeWindow(m_app, this);
    m_analyzeWindow->setModal(true);
    if(m_analyzeWindow->exec())
    {
        QModelIndex index = model.setRootPath(m_app.getAnalizedFolderPath());

        m_ui.filesTree->setModel(&model);
        m_ui.filesTree->setRootIndex(index);
        m_ui.filesTree->hideColumn(2);
        m_ui.filesTree->hideColumn(3);

        m_app.buildSourceCodeBlocks();
    }
    else ;//

    /*
    QTabWidget* filesTab = m_ui.filesTab;
    CodeRenderWindow* render = new CodeRenderWindow(m_app, this);
    int index = filesTab->addTab(render, QString("Renderer"));
    filesTab->setCurrentIndex(index);
    */
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