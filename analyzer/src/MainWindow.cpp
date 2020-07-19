#include "MainWindow.h"
#include <QFileDialog.h>
#include <QTextEdit.h>
#include <QTextStream.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_ui.setupUi(this);

    QList<int> widths = {200, 400};
    m_ui.splitter->setSizes(widths);

    connect(m_ui.actionExplore_Folder, SIGNAL(triggered()), this, SLOT(file_explore_folder()));
    connect(m_ui.filesTree, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(handleDoubleClick(const QModelIndex &)));
    connect(m_ui.filesTab, SIGNAL(tabCloseRequested(int)), this, SLOT(handleCloseRequest(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::file_explore_folder()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);

    if(fileDialog.exec())
    {
        QModelIndex index = model.setRootPath(fileDialog.selectedFiles().first());

        m_ui.filesTree->setModel(&model);
        m_ui.filesTree->setRootIndex(index);
        m_ui.filesTree->hideColumn(2);
        m_ui.filesTree->hideColumn(3);
    }
}

void MainWindow::handleDoubleClick(const QModelIndex& modelIndex)
{
    QTabWidget* filesTab = m_ui.filesTab;
    QString absoluteFilePath = model.filePath(modelIndex);

    QFile file(absoluteFilePath);
    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly))
        {
            QStringList absoluteFilePathSplitted = absoluteFilePath.split("/");

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

void MainWindow::handleCloseRequest(int index)
{
    QTabWidget* filesTab = m_ui.filesTab;

    QWidget* deletedTabs = filesTab->widget(index);
    filesTab->removeTab(index);

    delete deletedTabs;
}