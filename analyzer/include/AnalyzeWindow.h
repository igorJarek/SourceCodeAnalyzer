#pragma once

#include "SourceCodeView.h"

#include <QDialog>
#include <ui_AnalyzeWindow.h>

class App;

class AnalyzeWindow : public QDialog
{
    Q_OBJECT

public:
    AnalyzeWindow(App& app, const QStringList& args, QWidget *parent = Q_NULLPTR);
    ~AnalyzeWindow();

public:
    QSharedPointer<SourceCodeView> getNewSourceCodeView() { return m_newSourceCodeView; }

private:
    void initUi();
    void initSignalsConnections();

private:
    Ui::AnalyzeWindow   m_ui;

    App&                m_app;
     const QStringList& m_args;

     QSharedPointer<SourceCodeView> m_newSourceCodeView;

private slots:
    void              start();
    void              cancel();
};
