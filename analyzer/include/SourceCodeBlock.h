#pragma once

#include <QTextDocument>
#include <QStaticText>
#include <QPainter>
#include <QVector>

class Token : public QStaticText
{
    public:
        Token();
        ~Token();

    private:
        // kolor
};

class SourceCodeBlock : public QTextDocument
{
    public:
        SourceCodeBlock(QPainter& painter);
        ~SourceCodeBlock();

    private:
        QPainter& m_painter;

        QVector<QVector<Token>> m_tokens;
};
