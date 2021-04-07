#include "CreateDatabaseWindow.h"
#include <App.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QScopedPointer>
#include <QTreeWidget>

#include <DatabaseBuilder/DatabaseBuilder.h>
#include <FolderBrowser/FolderBrowser.h>

CreateDatabaseWindow::CreateDatabaseWindow(App& app, QWidget *parent) :
    m_app(app), QDialog(parent)
{
    initUi();
    initSignalsConnections();
}

CreateDatabaseWindow::~CreateDatabaseWindow()
{

}

void CreateDatabaseWindow::initUi()
{
    m_ui.setupUi(this);

    m_ui.progressBar->hide();
    m_ui.analyzedFilePath->hide();

    //m_ui.folderPathEdit->setText("D:\\Programowanie\\SourceCodeAnalyzer\\lib");
    //m_analizedFolderPath = "D:\\Programowanie\\SourceCodeAnalyzer\\lib";

    //m_ui.includeFolderEdit->append("D:\\Programowanie\\SourceCodeAnalyzer\\lib\\include");
    //m_includePaths.append("D:\\Programowanie\\SourceCodeAnalyzer\\lib\\include");
}

void CreateDatabaseWindow::initSignalsConnections()
{
    connect(m_ui.folderPathButton,      SIGNAL(clicked()), this, SLOT(folder_path()));
    connect(m_ui.includeFolderButton,   SIGNAL(clicked()), this, SLOT(include_path()));
    connect(m_ui.removeFolderButton,    SIGNAL(clicked()), this, SLOT(remove_path()));

    connect(m_ui.startButton,           SIGNAL(clicked()), this, SLOT(start()));
    connect(m_ui.cancelButton,          SIGNAL(clicked()), this, SLOT(cancel()));
}

void CreateDatabaseWindow::folder_path()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);

    if(fileDialog.exec())
    {
        QString folderPath = fileDialog.selectedFiles().first();
        folderPath.replace('/', '\\');
        m_analizedFolderPath = folderPath;
        m_ui.folderPathEdit->setText(folderPath);
    }
}

void CreateDatabaseWindow::include_path()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);

    if(fileDialog.exec())
    {
        QString includePath = fileDialog.selectedFiles().first();
        includePath.replace('/', '\\');

        QList<QTreeWidgetItem*> findDuplicate = m_ui.includeFolderTree->findItems(includePath, Qt::MatchExactly, 0); 

        if(findDuplicate.size())
            QMessageBox::warning(this, "Include Path", includePath + " path exists in include list.", QMessageBox::StandardButton::Ok);
        else
        {
            QTreeWidgetItem* includeItem = new QTreeWidgetItem(m_ui.includeFolderTree);
            includeItem->setText(0, includePath);
        }
    }
}

void CreateDatabaseWindow::remove_path()
{
    QList<QTreeWidgetItem*> selectedPaths =  m_ui.includeFolderTree->selectedItems();

    for(QTreeWidgetItem* selectedPath : selectedPaths)
    {
        int index = m_ui.includeFolderTree->indexOfTopLevelItem(selectedPath);
        m_ui.includeFolderTree->takeTopLevelItem(index);
    }
}

void CreateDatabaseWindow::start()
{
    if(m_analizedFolderPath.isEmpty())
    {
        QMessageBox::warning(this, "Analyzed Folder", "Choose analyzed folder.", QMessageBox::StandardButton::Ok);
        return;
    }

    if(!m_app.getDatabase())
        m_app.allocateDatabase();
    else
        m_app.reallocateDatabase();

    Database& database = *m_app.getDatabase();

    FolderBrowser folderBrowser;
    folderBrowser.setFileTypeBrowser(FileType::SOURCE_AND_HEADER_FILE);
    folderBrowser.startFolderBrowse(m_analizedFolderPath.toStdString());

    int32_t includeCount = m_ui.includeFolderTree->topLevelItemCount() + 1;
    int32_t compilationArgsCount = includeCount * 2;

    QScopedArrayPointer<QByteArray>  tmpArgs         = QScopedArrayPointer<QByteArray>(new QByteArray[includeCount]);
    QScopedArrayPointer<const char*> compilationArgs = QScopedArrayPointer<const char*>(new const char*[compilationArgsCount]);

    QTreeWidgetItemIterator includeFolderIterator(m_ui.includeFolderTree);
    int32_t index = 0;

    while(*includeFolderIterator)
    {
        tmpArgs[index].append((*includeFolderIterator)->text(0).toLocal8Bit().constData());

        compilationArgs[index * 2 + 0] = "-I";
        compilationArgs[index * 2 + 1] = tmpArgs[index];

        ++index;
        ++includeFolderIterator;
    }

    compilationArgs[index * 2 + 0] = "--std";

    if(m_ui.cpp98radiobutton->isChecked())
        compilationArgs[index * 2 + 1] = "c++98";
    else if(m_ui.cpp03radiobutton->isChecked())
        compilationArgs[index * 2 + 1] = "c++03";
    else if(m_ui.cpp11radiobutton->isChecked())
        compilationArgs[index * 2 + 1] = "c++11";
    else if(m_ui.cpp14radiobutton->isChecked())
        compilationArgs[index * 2 + 1] = "c++14";
    else if(m_ui.cpp17radiobutton->isChecked())
        compilationArgs[index * 2 + 1] = "c++17";
    else
    {
        QMessageBox::warning(this, "Analyzed Folder", "Choose C++ standard.", QMessageBox::StandardButton::Ok);
        return;
    }

    DatabaseBuilder databaseBuilder(database, "Analyzer", "0.1alpha", folderBrowser, compilationArgs.get(), compilationArgsCount);

    QProgressBar* progressBar = m_ui.progressBar;
    progressBar->show();
    progressBar->setMinimum(0);
    progressBar->setMaximum(folderBrowser.getFileCount());
    progressBar->setValue(0);

    QLabel* label = m_ui.analyzedFilePath;
    label->show();

    databaseBuilder.buildDatabase
    (
        [&progressBar, &label](const string& filePath, size_t fileIndex, size_t fileCount) -> void
        {
            progressBar->setValue(fileIndex);
            label->setText(QString::fromStdString(filePath));
            label->adjustSize();
        }
    );

    m_app.setAnalizedFolderPath(m_analizedFolderPath);

    accept();
}

void CreateDatabaseWindow::cancel()
{
    close();
}
