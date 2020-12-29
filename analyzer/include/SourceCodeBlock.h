#pragma once

#include <QSharedPointer>
#include <QTextDocument>
#include <QStaticText>
#include <QPainter>
#include <QVector>

#include <list>

class QueryResults;

class SourceCodeBlockToken : public QStaticText
{
    public:
        SourceCodeBlockToken() {}
        ~SourceCodeBlockToken() {}

    public:
        void     setKind(uint16_t kind)               { m_kind = kind; }
        void     setStartColPos(uint32_t startColPos) { m_startColPos = startColPos; }
        void     setEndColPos(uint32_t endColPos)     { m_endColPos = endColPos; }
        void     setIsCalling(bool isCalling)         { m_isCalling = isCalling; }


        uint16_t getKind()        const               { return m_kind; }
        uint32_t getStartColPos() const               { return m_startColPos; }
        uint32_t getEndColPos()   const               { return m_endColPos; }
        bool     getIsCalling()   const               { return m_isCalling; }

    private:
        uint16_t m_kind = 0;

        uint32_t m_startColPos = 0;
        uint32_t m_endColPos = 0;

        bool     m_isCalling = false;
};

class SourceCodeBlock
{
    public:
        SourceCodeBlock(QueryResults& tokenResults, QueryResults& callingResults);
        ~SourceCodeBlock();

        static uint16_t getPadding() { return 10; }
        static uint16_t getBorderWidth() { return 5; }

    public:
        uint32_t getWidth()  { return m_width; }
        uint32_t getHeight() { return m_height; }

        void draw(QPainter& painter, QFontMetrics& fontMetrics);

    private:
        QVector<QSharedPointer<std::list<SourceCodeBlockToken>>> m_tokens;
        uint32_t m_width  = 0;
        uint32_t m_height = 0;
};
