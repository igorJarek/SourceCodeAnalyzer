#pragma once

#include "App.h"
#include "ui_MainWindow.h"

#include <QtWidgets/QMainWindow>
#include <QDir.h>
#include <QFileSysteMmodel.h>
#include <QTreeWidget.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(App& app, QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private:
    void                    initUi();
    void                    initSignalsConnections();

private:
    Ui::MainWindowClass     m_ui;
    App&                    m_app;

    QFileSystemModel        model;

private slots:
    void                    create_database();
    void                    open_database();
    void                    save_as_database();
    void                    save_database();
    void                    start_analyze();
    void                    exit();

    void                    filesTree_doubleClick(const QModelIndex& modelIndex);
    void                    filesTab_closeTab(int index);
};
