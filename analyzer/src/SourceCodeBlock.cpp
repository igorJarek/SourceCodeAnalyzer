#include <SourceCodeBlock.h>
#include <Database/Database.h>

#include <QMessageBox>
#include <clang-c/Index.h>

SourceCodeBlock::SourceCodeBlock(QueryResults& tokenResults, QueryResults& callingResults)
{
    uint32_t currentLine = 0;

    for(std::vector<std::string>& tokenRow : tokenResults.rows)
    {
        uint32_t     tokenID            = std::stoll(tokenRow[0]);
        uint16_t     tokenKind          = std::stoi(tokenRow[1]);
        std::string& tokenSpelling      = tokenRow[2];
        uint32_t     tokenStartPos_Line = std::stoll(tokenRow[3]);
        uint32_t     tokenStartPos_Col  = std::stoll(tokenRow[4]);
        uint32_t     tokenEndPos_Line   = std::stoll(tokenRow[5]);
        uint32_t     tokenEndPos_Col    = std::stoll(tokenRow[6]);

        if(tokenStartPos_Line != tokenEndPos_Line)
            QMessageBox::critical(nullptr, "Token Error", "tokenStartPos_Line != tokenEndPos_Line", QMessageBox::StandardButton::Ok);
        else
        {
            SourceCodeBlockToken token;
            token.setText(QString::fromStdString(tokenSpelling));

            token.setKind(tokenKind);
            token.setStartColPos(tokenStartPos_Col);
            token.setEndColPos(tokenEndPos_Col);

            for(std::vector<std::string>& callingRow : callingResults.rows)
            {
                uint32_t callingNameTokenID = std::stoll(callingRow[1]);
                if(tokenID == callingNameTokenID)
                    token.setIsCalling(true);
            }

            if(currentLine != tokenStartPos_Line)
            {
                currentLine = tokenStartPos_Line;
                m_tokens.append(QSharedPointer<std::list<SourceCodeBlockToken>>(new std::list<SourceCodeBlockToken>));
            }

            m_tokens.last()->push_back(token);
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
    QPen penCallings(QColor(255, 0, 0));

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
            for(SourceCodeBlockToken& token : *m_tokens[tokenIndex])
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
                else if(token.getKind() == CXToken_Identifier)
                {
                    if(token.getIsCalling())
                    {
                        painter.setPen(penCallings);
                        painter.drawStaticText(QPoint(x, y), token);
                        painter.setPen(penWhite);
                    }
                    else
                        painter.drawStaticText(QPoint(x, y), token);
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

    m_width  = xMax + getBorderWidth() + getPadding();
    m_height = y + lineSpacing + getPadding();

    painter.setPen(penRed);
    painter.drawRect(0, 0, m_width, m_height);
}
