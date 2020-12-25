#pragma once

#include <QDialog>
#include <QStringList>
#include <ui_AnalyzeWindow.h>

class App;

class AnalyzeWindow : public QDialog
{
    Q_OBJECT

public:
    AnalyzeWindow(App& app, QWidget *parent = Q_NULLPTR);
    ~AnalyzeWindow();

private:
    void initUi();
    void initSignalsConnections();

private:
    Ui::AnalyzeWindow m_ui;

    App&              m_app;

    QString           m_mainFilePath;
    QString           m_functionName;
    int32_t           m_functionLine;

private slots:
    void              main_folder();
    void              start();
    void              cancel();
};
