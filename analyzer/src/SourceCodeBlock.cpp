#include <SourceCodeBlock.h>
#include <Database/Database.h>

#include <QMessageBox>
#include <clang-c/Index.h>

SourceCodeBlock::SourceCodeBlock(QueryResults& tokenResults, int32_t lineCount)
{
    m_tokens.resize(lineCount);

    for(std::vector<std::string>& row : tokenResults.rows)
    {
        uint16_t     tokenKind          = std::stoi(row[1]);
        std::string& tokenSpelling      = row[2];
        uint32_t     tokenStartPos_Line = std::stoll(row[3]);
        uint32_t     tokenStartPos_Col  = std::stoll(row[4]);
        uint32_t     tokenEndPos_Line   = std::stoll(row[5]);
        uint32_t     tokenEndPos_Col    = std::stoll(row[6]);

        if(tokenStartPos_Line != tokenEndPos_Line)
            QMessageBox::critical(nullptr, "Token Error", "tokenStartPos_Line != tokenEndPos_Line", QMessageBox::StandardButton::Ok);
        else
        {
            Token token;
            token.setText(QString::fromStdString(tokenSpelling));

            token.setKind(tokenKind);
            token.setStartColPos(tokenStartPos_Col);
            token.setEndColPos(tokenEndPos_Col);

            if(!m_tokens[tokenStartPos_Line-1])
                m_tokens[tokenStartPos_Line-1] = QSharedPointer<std::list<Token>>(new std::list<Token>);

            m_tokens[tokenStartPos_Line-1]->push_back(token);
        }
    }
}

SourceCodeBlock::~SourceCodeBlock()
{

}

void SourceCodeBlock::draw(QPainter& painter, QFontMetrics& fontMetrics)
{
    QPen penWhite(Qt::white);
    QPen penKeywords(QColor(78, 201, 176));
    QPen penLiterals(QColor(214, 157, 133));

    QPen penRed(QColor(180, 0, 80));
    penRed.setWidth(getBorderWidth());

    painter.setPen(penWhite);

    uint32_t lineSpacing = fontMetrics.lineSpacing();
    uint32_t spaceWidth = fontMetrics.width(" ");
    uint32_t x = getBorderWidth() + getPadding(), y = getBorderWidth() + getPadding();
    uint32_t lastTokenEndCol = 0;

    uint32_t xMax = 0;

    for(uint64_t tokenIndex = 0; tokenIndex < m_tokens.size(); ++tokenIndex)
    {
        if(m_tokens[tokenIndex]) // prevent against empty line
        {
            for(Token& token : *m_tokens[tokenIndex])
            {
                if(lastTokenEndCol)
                {
                    uint32_t spacesNeeded = token.getStartColPos() - lastTokenEndCol;
                    if(spacesNeeded)
                        x += spaceWidth * spacesNeeded;
                }
                else
                {
                    uint32_t startColPos = token.getStartColPos();
                    if(startColPos)
                        x += startColPos * spaceWidth;
                }

                if(token.getKind() == CXToken_Keyword)
                {
                    painter.setPen(penKeywords);
                    painter.drawStaticText(QPoint(x, y), token);
                    painter.setPen(penWhite);
                }
                else if(token.getKind() == CXToken_Literal)
                {
                    painter.setPen(penLiterals);
                    painter.drawStaticText(QPoint(x, y), token);
                    painter.setPen(penWhite);
                }
                else
                    painter.drawStaticText(QPoint(x, y), token);

                x += fontMetrics.width(token.text());
                lastTokenEndCol = token.getEndColPos();

                if(x > xMax)
                    xMax = x;
            }
        }

        x = getBorderWidth() + getPadding();
        y += lineSpacing;
        lastTokenEndCol = 0;
    }

    painter.setPen(penRed);
    painter.drawRect(0, 0, xMax + getBorderWidth() + getPadding(), y - lineSpacing + getPadding());
}
