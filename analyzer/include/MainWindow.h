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

    void                    openCodeRenderWindow(QSharedPointer<SourceCodeView> view);

    void                    fillDatabaseTree();
    void                    fillViewsTree(QSharedPointer<SourceCodeView> view);

private:
    Ui::MainWindowClass     m_ui;
    App&                    m_app;

private slots:
    void                    create_database();
    void                    open_database();
    void                    save_as_database();
    void                    exit();

    void                    create_view();
    void                    save_view_as_svg();

    void                    databaseTree_contextMenu(const QPoint& point);
    void                    close_view(int index);
    void                    open_view(QTreeWidgetItem* item, int column);
    void                    viewsTree_contextMenu(const QPoint& point);
};
