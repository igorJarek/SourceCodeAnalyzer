#pragma once

#include <QSharedPointer>
#include <QTextDocument>
#include <QStaticText>
#include <QPainter>
#include <QVector>

#include <list>

class QueryResults;

class Token : public QStaticText
{
    public:
        Token() {}
        ~Token() {}

    public:
        void     setKind(uint16_t kind)               { m_kind = kind; }
        void     setStartColPos(uint32_t startColPos) { m_startColPos = startColPos; }
        void     setEndColPos(uint32_t endColPos)     { m_endColPos = endColPos; }

        uint16_t getKind()        const               { return m_kind; }
        uint32_t getStartColPos() const               { return m_startColPos; }
        uint32_t getEndColPos()   const               { return m_endColPos; }

    private:
        uint16_t m_kind = 0;

        uint32_t m_startColPos = 0;
        uint32_t m_endColPos = 0;
};

class SourceCodeBlock
{
    public:
        SourceCodeBlock(QueryResults& tokenResults, int32_t lineCount);
        ~SourceCodeBlock();

        static uint16_t getPadding() { return 10; }
        static uint16_t getBorderWidth() { return 5; }

    public:
        void draw(QPainter& painter, QFontMetrics& fontMetrics);

    private:
        QVector<QSharedPointer<std::list<Token>>> m_tokens;
};
