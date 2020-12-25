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

    if(!filePath.isEmpty())
    {
        m_mainFilePath = filePath;
        m_ui.mainFilePath->setText(filePath);
    }
}

void AnalyzeWindow::start()
{
    m_functionName = m_ui.functionName->text();

    bool isConvOk;
    m_functionLine = m_ui.functionLine->text().toInt(&isConvOk, 10);

    if(m_mainFilePath.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Main File Path must be not empty");
        return;
    }

    if(m_functionName.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Function Name must be not empty");
        return;
    }

    if(!isConvOk || m_functionLine < 0)
    {
        QMessageBox::warning(this, "Warning", "Line Number must be integer number and greater than 0");
        return;
    }


}

void AnalyzeWindow::cancel()
{
    close();
}
