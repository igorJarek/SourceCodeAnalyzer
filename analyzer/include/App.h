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
    QSharedPointer<Database>                 getDatabase() { return m_database; }
    void                                     reallocateDatabase(const QString& databasePath);
    void                                     allocateDatabase(const QString& databasePath);

    void                                     setAnalizedFolderPath(QString& path) { m_analyzedFolderPath = path; }
    const QString&                           getAnalizedFolderPath() const        { return m_analyzedFolderPath; }

    void                                     buildSourceCodeBlocks();
private:
    QSharedPointer<Database>                 m_database = nullptr;
    QString                                  m_analyzedFolderPath;

    QVector<QSharedPointer<SourceCodeBlock>> m_sourceCodeBlocks;                     
};