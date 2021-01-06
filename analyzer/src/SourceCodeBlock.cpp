#include <SourceCodeBlock.h>
#include <Database/Database.h>

#include <QMessageBox>
#include <clang-c/Index.h>

SourceCodeBlock::SourceCodeBlock(const QString& filePath, QueryResults& tokenResults, QueryResults& callingResults) :
    m_filePath(filePath)
{
    prepareTokens(tokenResults, callingResults);
    prepareTokensPos();
}

SourceCodeBlock::~SourceCodeBlock()
{

}

void SourceCodeBlock::prepareTokens(QueryResults& tokenResults, QueryResults& callingResults)
{
    uint32_t currentLine = 0;

    m_filePathText = QSharedPointer<SourceCodeBlockText>(new SourceCodeBlockText(m_filePath));

    for(std::vector<std::string>& tokenRow : tokenResults.rows)
    {
        uint32_t     tokenID            = std::stoll(tokenRow[0]);
        uint16_t     tokenKind          = std::stoi(tokenRow[1]);
        std::string& tokenSpelling      = tokenRow[2];
        uint32_t     tokenStartPos_Line = std::stoll(tokenRow[3]);
        uint32_t     tokenStartPos_Col  = std::stoll(tokenRow[4]);
        uint32_t     tokenEndPos_Line   = std::stoll(tokenRow[5]);
        uint32_t     tokenEndPos_Col    = std::stoll(tokenRow[6]);

        if(currentLine == 0)
        {
            currentLine = tokenStartPos_Line;

            QSharedPointer<SourceCodeBlockText> currentLineText = QSharedPointer<SourceCodeBlockText>(new SourceCodeBlockText(QString::number(currentLine) + "."));

            m_lineCounter.append(currentLineText);
            m_tokens.append(QSharedPointer<std::list<QSharedPointer<SourceCodeBlockToken>>>(new std::list<QSharedPointer<SourceCodeBlockToken>>));
        }

        if(tokenStartPos_Line != tokenEndPos_Line)
            QMessageBox::critical(nullptr, "Token Error", "tokenStartPos_Line != tokenEndPos_Line", QMessageBox::StandardButton::Ok);
        else
        {
            QSharedPointer<SourceCodeBlockToken> token = QSharedPointer<SourceCodeBlockToken>(new SourceCodeBlockToken);
            token->setText(QString::fromStdString(tokenSpelling));

            token->setKind(tokenKind);
            token->setStartColPos(tokenStartPos_Col);
            token->setEndColPos(tokenEndPos_Col);

            for(std::vector<std::string>& callingRow : callingResults.rows)
            {
                uint32_t callingNameTokenID = std::stoll(callingRow[1]);
                if(tokenID == callingNameTokenID)
                    token->setIsCalling(true);
            }

            while(currentLine != tokenStartPos_Line)
            {
                ++currentLine;

                m_tokens.append(QSharedPointer<std::list<QSharedPointer<SourceCodeBlockToken>>>(new std::list<QSharedPointer<SourceCodeBlockToken>>));

                QSharedPointer<SourceCodeBlockText> currentLineText = QSharedPointer<SourceCodeBlockText>(new SourceCodeBlockText(QString::number(currentLine) + "."));
                m_lineCounter.append(currentLineText);
            }

            m_tokens.last()->push_back(token);
        }
    }
}

void SourceCodeBlock::prepareTokensPos()
{
    QFont        font10("Consolas", 10, 10);
    QFont        font15("Consolas", 13, 13);
    QFontMetrics font10Metrics(font10);
    QFontMetrics font15Metrics(font15);

    uint32_t lineSpacing          = font10Metrics.lineSpacing();
    uint32_t spaceWidth           = font10Metrics.width(" ");
    uint32_t x                    = getBorderWidth() / 2 + getPadding();
    uint32_t y                    = getBorderWidth() / 2 + getPadding();
    uint32_t lastTokenEndCol      = 0;
    uint16_t callingInLineCounter = 0;

    uint32_t xMax                 = 0;

    m_filePathText->setPosX(x);
    m_filePathText->setPosY(y);

    if(font15Metrics.width(m_filePathText->text() > xMax))
        xMax = font15Metrics.width(m_filePathText->text());

    y += font15Metrics.lineSpacing() + getPadding();

    m_filePathLine = QLine(0, y, 0, y);

    y += getPadding();

    for(uint64_t lineIndex = 0; lineIndex < m_tokens.size(); ++lineIndex)
    {
        m_lineCounter[lineIndex]->setPosX(x);
        m_lineCounter[lineIndex]->setPosY(y);

        x += spaceWidth * 6;

        if(m_tokens[lineIndex]) // prevent against empty line
        {
            callingInLineCounter = 0;

            for(QSharedPointer<SourceCodeBlockToken>& token : *m_tokens[lineIndex])
            {
                if(lastTokenEndCol)
                {
                    uint32_t spacesNeeded = token->getStartColPos() - lastTokenEndCol;
                    if(spacesNeeded)
                        x += spaceWidth * spacesNeeded;
                }
                else
                {
                    uint32_t startColPos = token->getStartColPos();
                    if(startColPos)
                        x += startColPos * spaceWidth;
                }

                token->setPosX(x);
                token->setPosY(y);

                x += font10Metrics.width(token->text());
                lastTokenEndCol = token->getEndColPos();

                if(token->getIsCalling())
                    ++callingInLineCounter;
            }
        }

        while(callingInLineCounter)
        {
            --callingInLineCounter;

            m_callingFirstPos.append(QPoint(x + 20, y + lineSpacing / 2));
        }

        if(x > xMax)
            xMax = x;

        x = getBorderWidth() / 2 + getPadding();
        y += lineSpacing;
        lastTokenEndCol = 0;
    }

    m_size.setX(xMax + (getBorderWidth() / 2 + 1) + 2 * getPadding());
    m_size.setY(y + getPadding());
}

void SourceCodeBlock::draw(QPainter& painter)
{
    QFont font10("Consolas", 10, 10);
    QFont font15("Consolas", 13, 13);

    QPen penWhite(Qt::white);
    QPen penFilePath(Qt::yellow);
    QPen penLines(QColor(43, 145, 175));
    QPen penKeywords(QColor(78, 201, 176));
    QPen penLiterals(QColor(214, 157, 133));
    QPen penCallings(QColor(255, 0, 0));

    QPen penBorder(QColor(180, 0, 80));

    painter.setFont(font15);
    painter.setPen(penFilePath);

    painter.drawStaticText(m_filePathText->getPos(), *m_filePathText);

    painter.setFont(font10);
    painter.setPen(penWhite);

    for(uint64_t lineIndex = 0; lineIndex < m_tokens.size(); ++lineIndex)
    {
        painter.setPen(penLines);
        painter.drawStaticText(m_lineCounter[lineIndex]->getPos(), *m_lineCounter[lineIndex]);
        painter.setPen(penWhite);

        if(m_tokens[lineIndex]) // prevent against empty line
        {
            for(QSharedPointer<SourceCodeBlockToken>& token : *m_tokens[lineIndex])
            {
                if(token->getKind() == CXToken_Keyword)
                    painter.setPen(penKeywords);
                else if(token->getKind() == CXToken_Literal)
                    painter.setPen(penLiterals);
                else if(token->getKind() == CXToken_Identifier)
                {
                    if(token->getIsCalling())
                        painter.setPen(penCallings);
                }

                painter.drawStaticText(token->getPos(), *token);
                painter.setPen(penWhite);
            }
        }
    }

    penBorder.setWidth(2);
    painter.setPen(penBorder);
    painter.drawLine(m_filePathLine);

    penBorder.setWidth(getBorderWidth());
    painter.setPen(penBorder);
    painter.drawRect(0, 0, m_size.x(), m_size.y());
}

void SourceCodeBlock::setWidth(int width)
{
    m_size.setX(width);
    m_filePathLine.setP2(QPoint(m_size.x(), m_filePathLine.p2().y()));
}

void SourceCodeBlock::setPosition(uint32_t x, uint32_t y)
{
    m_pos.setX(x);
    m_pos.setY(y);
}
