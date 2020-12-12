#include <SourceCodeBlock.h>

SourceCodeBlock::SourceCodeBlock(QPainter& painter) :
    m_painter(painter)
{
    QPen penRed(Qt::red);
    penRed.setWidth(5);
    penRed.setStyle(Qt::SolidLine);

    m_painter.setPen(penRed);
    m_painter.drawRect(20, 20, 400, 600);
}

SourceCodeBlock::~SourceCodeBlock()
{

}
