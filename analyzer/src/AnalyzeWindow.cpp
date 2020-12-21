#include "AnalyzeWindow.h"
#include <App.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QScopedPointer>

#include <DatabaseBuilder/DatabaseBuilder.hpp>
#include <FolderBrowser/FolderBrowser.h>

AnalyzeWindow::AnalyzeWindow(App& app, QWidget *parent) :
    m_app(app), QDialog(parent)
{
    initUi();
    initSignalsConnections();
}

AnalyzeWindow::~AnalyzeWindow()
{

}

void AnalyzeWindow::initUi()
{
    m_ui.setupUi(this);

    m_ui.progressBar->hide();
    m_ui.analyzedFilePath->hide();

    m_ui.folderPathEdit->setText("F:\\Programowanie\\SourceCodeAnalyzer\\lib");
    m_analizedFolderPath = "F:\\Programowanie\\SourceCodeAnalyzer\\lib";

    m_ui.includeFolderEdit->append("F:\\Programowanie\\SourceCodeAnalyzer\\lib\\include");
    m_includePaths.append("F:\\Programowanie\\SourceCodeAnalyzer\\lib\\include");
}

void AnalyzeWindow::initSignalsConnections()
{
    connect(m_ui.folderPathButton,      SIGNAL(clicked()), this, SLOT(folder_path()));
    connect(m_ui.includeFolderButton,   SIGNAL(clicked()), this, SLOT(include_path()));
    connect(m_ui.databasePathButton,    SIGNAL(clicked()), this, SLOT(database_path()));
    connect(m_ui.startButton,           SIGNAL(clicked()), this, SLOT(start()));
}

void AnalyzeWindow::folder_path()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);

    if(fileDialog.exec())
    {
        QString folderPath = fileDialog.selectedFiles().first();
        m_analizedFolderPath = folderPath;
        m_ui.folderPathEdit->setText(folderPath);
    }
}

void AnalyzeWindow::database_path()
{
   QString filter = tr("SQLite File (*.sqlite3)");
   QString filePath = QFileDialog::getSaveFileName(this, tr("Database Path"), QString(), tr("SQLite File (*.sqlite3)"), &filter);

    if(!filePath.isEmpty())
    {
        m_databasePath = filePath;
        m_ui.databaseFolderPath->setText(filePath);
    }
}

void AnalyzeWindow::include_path()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setOption(QFileDialog::ShowDirsOnly);

    if(fileDialog.exec())
    {
        QString includePath = fileDialog.selectedFiles().first();
        if(m_includePaths.contains(includePath))
            QMessageBox::warning(this, "Include Path", includePath + " path exists in include list.", QMessageBox::StandardButton::Ok);
        else
        {
            m_ui.includeFolderEdit->append(includePath);
            m_includePaths.append(includePath);
        }
    }
}

void AnalyzeWindow::start()
{
    if(m_analizedFolderPath.isEmpty())
    {
        QMessageBox::warning(this, "Analyzed Folder", "Choose analyzed folder.", QMessageBox::StandardButton::Ok);
        reject();
        return;
    }

    if(m_databasePath.isEmpty())
    {
        QMessageBox::warning(this, "Database File", "Choose database file.", QMessageBox::StandardButton::Ok);
        reject();
        return;
    }

    if(!m_app.getDatabase())
        m_app.allocateDatabase(m_databasePath);
    else
        m_app.reallocateDatabase(m_databasePath);

    Database& database = *m_app.getDatabase();

    FolderBrowser folderBrowser;
    folderBrowser.setFileTypeBrowser(FileType::SOURCE_FILE);
    folderBrowser.startFolderBrowse(m_analizedFolderPath.toStdString());

    int32_t includeCount = m_includePaths.size();
    QScopedArrayPointer<QByteArray>  tmpArgs         = QScopedArrayPointer<QByteArray>(new QByteArray[includeCount]);
    QScopedArrayPointer<const char*> compilationArgs = QScopedArrayPointer<const char*>(new const char*[includeCount * 2]);

    for(int32_t index = 0; index < includeCount; ++index)
    {
        tmpArgs[index].append(m_includePaths.at(index).toLocal8Bit().constData());

        compilationArgs[index * 2 + 0] = "-I";
        compilationArgs[index * 2 + 1] = tmpArgs[index];
    }

    DatabaseBuilder databaseBuilder(database, "Analyzer", "0.1alpha", folderBrowser, compilationArgs.get(), 2);

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
