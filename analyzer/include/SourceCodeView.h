#pragma once

#include <functional>

#include <QSharedPointer>
#include <QString>
#include <QVector>
#include <QQueue>
#include <QSet>

#include "SourceCodeBlock.h"

class Database;

struct SourceCodeViewCalling
{
    std::string filePath;
    uint32_t    functionID = 0;

    QSharedPointer<SourceCodeBlock> caller = nullptr;
};

struct SourceCodeViewLines
{
    QLine firstLine;
    QLine secondLine;
};

class SourceCodeView
{
 public:
    SourceCodeView(const QSharedPointer<Database>& database, const QString& mainFilePath, const QString& mainFunctionName, int32_t mainFunctionLine);
    ~SourceCodeView();

    using SourceCodeBlockPtr    = QSharedPointer<SourceCodeBlock>;
    using SourceCodeBlockVecPtr = QSharedPointer<QVector<SourceCodeBlockPtr>>;

    using SourceCodeViewLinesPtr = QSharedPointer<SourceCodeViewLines>;

public:
    void draw(QPainter& painter, double zoom);

    void build(std::function<void (void)> stateStatus);

private:
    void findAndProcessMainFunction(std::function<void (void)> stateStatus);
    void iteratesCallsQueue(std::function<void (void)> stateStatus);
    void setSourceCodeBlocksAlignment();
    void generateConnectionLines();

private:
    const QSharedPointer<Database>& m_database;
    const QString&                  m_mainFilePath;
    const QString&                  m_mainFunctionName;
    const int32_t                   m_mainFunctionLine;

    QQueue<SourceCodeViewCalling>   m_functionCallsQueue;
    //QSet<QString>                 m_functionCallsSet;

    QVector<SourceCodeBlockVecPtr>  m_functionSourceCodeBlockVec;
    QVector<SourceCodeViewLinesPtr> m_lines;
};
