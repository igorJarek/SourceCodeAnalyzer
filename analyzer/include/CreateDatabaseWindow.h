#pragma once

#include <QDialog>
#include <QStringList>
#include <ui_CreateDatabaseWindow.h>

class App;

class CreateDatabaseWindow : public QDialog
{
    Q_OBJECT

public:
    CreateDatabaseWindow(App& app, QWidget *parent = Q_NULLPTR);
    ~CreateDatabaseWindow();

private:
    void                     initUi();
    void                     initSignalsConnections();

private:
    Ui::CreateDatabaseWindow m_ui;

    App&                     m_app;

    QString                  m_analizedFolderPath;

private slots:
    void                     folder_path();
    void                     include_path();
    void                     remove_path();
    void                     start();
    void                     cancel();
};
