#pragma once

#include "App.h"
#include "ui_MainWindow.h"

#include <QtWidgets/QMainWindow>
#include <QDir>
#include <QFileSysteMmodel>
#include <QTreeWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(App& app, QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    void                    initUi();
    void                    initSignalsConnections();

    void                    fillDatabaseTree();

private:
    Ui::MainWindowClass     m_ui;
    App&                    m_app;

private slots:
    void                    create_database();
    void                    open_database();
    void                    save_as_database();
    void                    save_database();
    void                    exit();

    void                    create_view();

    void                    filesTab_closeTab(int index);
    void                    databaseTree_contextMenu(const QPoint& point);
};
