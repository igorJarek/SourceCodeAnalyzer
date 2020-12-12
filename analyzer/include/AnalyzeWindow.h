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
    Ui::Dialog m_ui;

    App& m_app;

    QString     m_analizedFolderPath;
    QStringList m_includePaths;
    QString     m_databasePath;

private slots:
    void folder_path();
    void include_path();
    void database_path();
    void start();
};
