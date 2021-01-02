#include "AnalyzeWindow.h"
#include "App.h"
#include "SourceCodeView.h"

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

    m_mainFilePath = "D:\\Programowanie\\SourceCodeAnalyzer\\lib\\Main.cpp";
    m_ui.mainFilePath->setText("D:\\Programowanie\\SourceCodeAnalyzer\\lib\\Main.cpp");

    m_ui.functionName->setText("main");
    m_ui.functionLine->setText("11");
}

void AnalyzeWindow::initSignalsConnections()
{
    connect(m_ui.mainFileButton, SIGNAL(clicked()), this, SLOT(main_folder()));
    connect(m_ui.startButton,    SIGNAL(clicked()), this, SLOT(start()));
    connect(m_ui.cancelButton,   SIGNAL(clicked()), this, SLOT(cancel()));
}

void AnalyzeWindow::main_folder()
{
    QString filter = tr("Source Code (*.c *.cpp *.h *.hpp)");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Source Code Path"), QString(), tr("Source Code (*.c *.cpp *.h *.hpp)"), &filter);
    filePath.replace('/', '\\');

    if(!filePath.isEmpty())
    {
        m_mainFilePath = filePath;
        m_ui.mainFilePath->setText(filePath);
    }
}

void AnalyzeWindow::start()
{
    QString functionName = m_ui.functionName->text();

    bool isConvOk;
    int32_t functionLine = m_ui.functionLine->text().toInt(&isConvOk, 10);

    if(m_mainFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Main File Path must be not empty");
        reject();
    }

    if(functionName.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Function Name must be not empty");
        reject();
    }

    if(!isConvOk || functionLine < 0)
    {
        QMessageBox::warning(this, "Warning", "Line Number must be integer number and greater than 0");
        reject();
    }

    QSharedPointer<SourceCodeView> sourceCodeView = QSharedPointer<SourceCodeView>(new SourceCodeView(m_app.getDatabase(), m_mainFilePath, functionName, functionLine));
    sourceCodeView->build
    (
        []() -> void
        {
            
        }
    );

    m_app.addSourceCodeView(sourceCodeView);

    accept();
}

void AnalyzeWindow::cancel()
{
    close();
}
