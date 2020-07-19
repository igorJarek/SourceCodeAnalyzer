/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionFolder;
    QAction *actionDatabase;
    QAction *actionOpen_2;
    QAction *actionExplore_Folder;
    QAction *actionVisual_Studio_Project;
    QAction *actionDatabase_2;
    QAction *actionSettings;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeView *filesTree;
    QTabWidget *filesTab;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOpen_2;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(800, 600);
        MainWindowClass->setMinimumSize(QSize(800, 600));
        actionFolder = new QAction(MainWindowClass);
        actionFolder->setObjectName(QString::fromUtf8("actionFolder"));
        actionDatabase = new QAction(MainWindowClass);
        actionDatabase->setObjectName(QString::fromUtf8("actionDatabase"));
        actionOpen_2 = new QAction(MainWindowClass);
        actionOpen_2->setObjectName(QString::fromUtf8("actionOpen_2"));
        actionExplore_Folder = new QAction(MainWindowClass);
        actionExplore_Folder->setObjectName(QString::fromUtf8("actionExplore_Folder"));
        actionVisual_Studio_Project = new QAction(MainWindowClass);
        actionVisual_Studio_Project->setObjectName(QString::fromUtf8("actionVisual_Studio_Project"));
        actionDatabase_2 = new QAction(MainWindowClass);
        actionDatabase_2->setObjectName(QString::fromUtf8("actionDatabase_2"));
        actionSettings = new QAction(MainWindowClass);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setMinimumSize(QSize(0, 0));
        splitter->setOrientation(Qt::Horizontal);
        filesTree = new QTreeView(splitter);
        filesTree->setObjectName(QString::fromUtf8("filesTree"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(filesTree->sizePolicy().hasHeightForWidth());
        filesTree->setSizePolicy(sizePolicy);
        filesTree->setMinimumSize(QSize(200, 0));
        splitter->addWidget(filesTree);
        filesTab = new QTabWidget(splitter);
        filesTab->setObjectName(QString::fromUtf8("filesTab"));
        filesTab->setMinimumSize(QSize(200, 0));
        filesTab->setElideMode(Qt::ElideNone);
        filesTab->setTabsClosable(true);
        filesTab->setMovable(true);
        splitter->addWidget(filesTab);

        horizontalLayout->addWidget(splitter);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuOpen_2 = new QMenu(menuFile);
        menuOpen_2->setObjectName(QString::fromUtf8("menuOpen_2"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExplore_Folder);
        menuFile->addSeparator();
        menuFile->addAction(menuOpen_2->menuAction());
        menuFile->addAction(actionSettings);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuOpen_2->addAction(actionVisual_Studio_Project);
        menuOpen_2->addAction(actionDatabase_2);

        retranslateUi(MainWindowClass);

        filesTab->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Analyzer", nullptr));
        actionFolder->setText(QApplication::translate("MainWindowClass", "Folder", nullptr));
        actionDatabase->setText(QApplication::translate("MainWindowClass", "Database", nullptr));
        actionOpen_2->setText(QApplication::translate("MainWindowClass", "Open", nullptr));
        actionExplore_Folder->setText(QApplication::translate("MainWindowClass", "Explore Folder", nullptr));
        actionVisual_Studio_Project->setText(QApplication::translate("MainWindowClass", "Visual Studio Project", nullptr));
        actionDatabase_2->setText(QApplication::translate("MainWindowClass", "Database", nullptr));
        actionSettings->setText(QApplication::translate("MainWindowClass", "Settings", nullptr));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", nullptr));
        menuOpen_2->setTitle(QApplication::translate("MainWindowClass", "Open ...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
