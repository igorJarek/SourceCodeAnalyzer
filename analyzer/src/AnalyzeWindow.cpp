#include "AnalyzeWindow.h"
#include "App.h"
#include "SourceCodeView.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QScopedPointer>

#include <DatabaseBuilder/DatabaseBuilder.h>
#include <FolderBrowser/FolderBrowser.h>

AnalyzeWindow::AnalyzeWindow(App& app, const QStringList& args, QWidget *parent) :
    m_app(app), m_args(args), QDialog(parent)
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
    connect(m_ui.startButton,    SIGNAL(clicked()), this, SLOT(start()));
    connect(m_ui.cancelButton,   SIGNAL(clicked()), this, SLOT(cancel()));
}

void AnalyzeWindow::start()
{
    const QString& viewName         = m_ui.viewNameEdit->text();
    const QString& mainFile         = m_args[0];
    const QString& functionName     = m_args[1];

    bool isConvOk;
    int32_t functionLine = m_args[2].toInt(&isConvOk, 10);

    if(viewName.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "View Name must be not empty");

        return;
    }

    if(m_app.isViewExists(viewName))
    {
        QMessageBox::warning(this, "Warning", "View '" + viewName + "' already exists");

        return;
    }

    if(mainFile.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Main File Path must be not empty");

        return;
    }

    if(functionName.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Function Name must be not empty");

        return;
    }

    if(!isConvOk || functionLine < 0)
    {
        QMessageBox::warning(this, "Warning", "Line Number must be integer number and greater than 0");

        return;
    }

    m_newSourceCodeView = QSharedPointer<SourceCodeView>(new SourceCodeView(m_app.getDatabase(), viewName, mainFile, m_app.getAnalizedFolderPath(), functionName, functionLine));
    m_newSourceCodeView->build
    (
        []() -> void
        {
            
        }
    );

    accept();
}

void AnalyzeWindow::cancel()
{
    close();
}
