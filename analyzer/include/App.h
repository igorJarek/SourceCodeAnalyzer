#pragma once

#include <Database/Database.h>
#include <SourceCodeBlock.h>

#include <QtWidgets/QApplication>
#include <QSharedPointer>
#include <QVector>

class App : public QApplication
{
public:
    App(int argc, char *argv[]);
    ~App();

public:
    QSharedPointer<Database>                        getDatabase() { return m_database; }

    void                                            reallocateDatabase();
    void                                            reallocateDatabase(const QString& databasePath);

    void                                            allocateDatabase();
    void                                            allocateDatabase(const QString& databasePath);

    const QVector<QSharedPointer<SourceCodeBlock>>& getSourceCodeBlocks() const          { return m_sourceCodeBlocks; }

    void                                            setAnalizedFolderPath(QString& path) { m_analyzedFolderPath = path; }
    const QString&                                  getAnalizedFolderPath() const        { return m_analyzedFolderPath; }

    void                                            setDatabasePath(QString& path)       { m_databasePath = path; }
    const QString&                                  getDatabasePath() const              { return m_databasePath; }

    void                                            buildSourceCodeBlocks();
private:
    QSharedPointer<Database>                        m_database = nullptr;
    QString                                         m_analyzedFolderPath;
    QString                                         m_databasePath;

    QVector<QSharedPointer<SourceCodeBlock>>        m_sourceCodeBlocks;
};
