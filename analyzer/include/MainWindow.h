#pragma once

#include <QtWidgets/QMainWindow>
#include <QDir.h>
#include <QFileSysteMmodel.h>
#include <QTreeWidget.h>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private slots:
    void file_explore_folder();
    void handleDoubleClick(const QModelIndex& modelIndex);
    void handleCloseRequest(int index);

private:
    Ui::MainWindowClass m_ui;

    QFileSystemModel model;
};
