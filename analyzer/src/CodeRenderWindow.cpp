#include <CodeRenderWindow.h>
#include <QPainter>
#include <QTextDocument>

CodeRenderWindow::CodeRenderWindow(App& app, QWidget *parent) :
    m_app(app), QWidget(parent)
{

}

void CodeRenderWindow::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.fillRect(QRect(0, 0, 3200, 3200), Qt::black);

    painter.translate(QPointF(100, 100));
    td.drawContents(&painter);
    painter.translate(QPointF(200, 200));
    td.drawContents(&painter);

    painter.end();

    //paint(painter);

    /*
    QPainter painter;
    painter.begin(this);
    //painter.setRenderHint(QPainter::Antialiasing);
    paint(painter);
    painter.end();
    */
}

void CodeRenderWindow::paint(QPainter &painter)
{
    /*QFont font = painter.font();
    font.setPixelSize(20);
    painter.setFont(font);
    painter.setPen(penBlue);
    painter.drawText(40, 40, QString("F:\Programowanie\SourceCodeAnalyzer\lib"));

    painter.setPen(penGreen);
    painter.drawText(40, 70, QString("main"));

    painter.setPen(penWhite);
    painter.drawText(40, 100, QString("1) int main()"));
    painter.drawText(40, 130, QString("2) {}"));*/
}

void CodeRenderWindow::wheelEvent(QWheelEvent * event)
{
    
}

/*
* QFontMetrics
* QTextDocument
* 
* 
* int id = QFontDatabase::addApplicationFont(":/fonts/monospace.ttf");
QString family = QFontDatabase::applicationFontFamilies(id).at(0);
QFont monospace(family);
*/