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
    void                initUi();
    void                initSignalsConnections();

private:
    Ui::MainWindowClass m_ui;
    App&                m_app;

    QFileSystemModel    model;

private slots:
    void                file_explore_folder();
    void                filesTree_doubleClick(const QModelIndex& modelIndex);
    void                filesTab_closeTab(int index);
};
