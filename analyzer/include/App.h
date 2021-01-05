#pragma once

#include <SourceCodeView.h>
#include <Database/Database.h>

#include <QtWidgets/QApplication>
#include <QSharedPointer>
#include <QMap>

class App : public QApplication
{
public:
    App(int argc, char *argv[]);
    ~App();

public:
    QSharedPointer<Database>                       getDatabase() { return m_database; }

    void                                           reallocateDatabase();
    void                                           reallocateDatabase(const QString& databasePath);

    void                                           allocateDatabase();
    void                                           allocateDatabase(const QString& databasePath);

    void                                           setAnalizedFolderPath(QString& path)                                         { m_analyzedFolderPath = path; }
    const QString&                                 getAnalizedFolderPath() const                                                { return m_analyzedFolderPath; }

    void                                           setDatabasePath(QString& path)                                               { m_databasePath = path; }
    const QString&                                 getDatabasePath() const                                                      { return m_databasePath; }

    bool                                           isViewExists(const QString& viewName);
    void                                           addSourceCodeView(const QSharedPointer<SourceCodeView>& sourceCodeView);
    QSharedPointer<SourceCodeView>                 getSourceCodeView(const QString& viewName)                                   { return m_sourceCodeViews[viewName]; }

private:
    QSharedPointer<Database>                       m_database           = nullptr;
    QString                                        m_analyzedFolderPath;
    QString                                        m_databasePath;

    QMap<QString, QSharedPointer<SourceCodeView>>  m_sourceCodeViews;
};
