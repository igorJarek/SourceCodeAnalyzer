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
        void     setPosX(uint32_t x)                  { m_pos.setX(x); }
        void     setPosY(uint32_t y)                  { m_pos.setY(y); }

        void     setKind(uint16_t kind)               { m_kind = kind; }
        void     setStartColPos(uint32_t startColPos) { m_startColPos = startColPos; }
        void     setEndColPos(uint32_t endColPos)     { m_endColPos = endColPos; }
        void     setIsCalling(bool isCalling)         { m_isCalling = isCalling; }

        QPoint   getPos()                             { return m_pos; }

        uint16_t getKind()        const               { return m_kind; }
        uint32_t getStartColPos() const               { return m_startColPos; }
        uint32_t getEndColPos()   const               { return m_endColPos; }
        bool     getIsCalling()   const               { return m_isCalling; }

    protected:
        QPoint   m_pos;

        uint16_t m_kind = 0;

        uint32_t m_startColPos = 0;
        uint32_t m_endColPos = 0;

        bool     m_isCalling = false;
};

class SourceCodeBlockText : public QStaticText // QGraphicsScene ?
{
    public:
        SourceCodeBlockText() {}
        SourceCodeBlockText(const QString& string) : QStaticText(string)
        {
            
        }

        ~SourceCodeBlockText() {}

    public:
        void   setPosX(uint32_t x) { m_pos.setX(x); }
        void   setPosY(uint32_t y) { m_pos.setY(y); }

        QPoint getPos()            { return m_pos; }

    protected:
        QPoint m_pos;
};

class SourceCodeBlock
{
    public:
        SourceCodeBlock(const QString& filePath, QueryResults& tokenResults, QueryResults& callingResults);
        ~SourceCodeBlock();

        static uint16_t getPadding() { return 10; }
        static uint16_t getBorderWidth() { return 3; }

    public:
        void   addDefinitions(QSharedPointer<SourceCodeBlock> def) { m_definitions.append(def); }

        QPoint getSize()     { return m_size; }
        QPoint getPosition() { return m_pos; };
        int    getWidth()    { return m_size.x(); }
        int    getHeight()   { return m_size.y(); }

        void   setWidth(int width);
        void   setPosition(uint32_t x, uint32_t y);

        QVector<QPoint>& getCallingFirstPos() { return m_callingFirstPos; }
        QSharedPointer<SourceCodeBlock> getIthDefinition(uint32_t i) { return m_definitions[i]; }

        void   draw(QPainter& painter);

    private:
        void   prepareTokens(QueryResults& tokenResults, QueryResults& callingResults);
        void   prepareTokensPos();

    private:
        QVector<QSharedPointer<SourceCodeBlockText>>                             m_lineCounter;
        QVector<QSharedPointer<std::list<QSharedPointer<SourceCodeBlockToken>>>> m_tokens;

        QString                                                                  m_filePath;
        QSharedPointer<SourceCodeBlockText>                                      m_filePathText;
        QLine                                                                    m_filePathLine;

        QVector<QPoint>                                                          m_callingFirstPos;
        QVector<QSharedPointer<SourceCodeBlock>>                                 m_definitions;

        QPoint m_size;
        QPoint m_pos;
};
