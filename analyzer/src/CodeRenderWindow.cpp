#include <CodeRenderWindow.h>
#include <SourceCodeBlock.h>
#include <App.h>

#include <QTextDocument>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

CodeRenderWindow::CodeRenderWindow(App& app, QWidget *parent) :
    m_app(app), QOpenGLWidget(parent), m_renderTarget(3000, 3000, QImage::Format_RGB32)
{
    /*
    QPainter     painter(this);
    QFont        font("JetBrains Mono", 10, 10);
    QFontMetrics fontMetrics(font);

    painter.setFont(font);
    painter.fillRect(QRect(0, 0, 3000, 3000), Qt::black);
    painter.setViewport(m_xPos - 20, m_yPos - 20, width(), height());

    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    QVector<SourceCodeView::SourceCodeBlockVecPtr>& sourceCodeBlockVec = latestSourceCodeView->getSourceCodeBlockVec();

    for(uint32_t i = 0; i < sourceCodeBlockVec.size(); ++i)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[i];
        painter.translate(m_xTranslate, m_yTranslate);
        painter.save();

        uint32_t maxStageWidth = 0;
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            const SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->at(j);
            sourceCodeBlockPtr->draw(painter, fontMetrics);

            painter.translate(0, sourceCodeBlockPtr->getHeight());

            if(sourceCodeBlockPtr->getWidth() > maxStageWidth)
                maxStageWidth = sourceCodeBlockPtr->getWidth();

            break;
        }

        painter.restore();

        m_xTranslate = maxStageWidth;
        m_yTranslate = 0;

        break;
    }

    painter.end();

    bool ret = m_renderTarget.save("image.png");
    int x = 10;
    */
}

void CodeRenderWindow::paintEvent(QPaintEvent * /* event */)
{
    QPainter     painter(this);
    QFont        font("JetBrains Mono", 10, 10);
    QFontMetrics fontMetrics(font);

    painter.setFont(font);
    painter.fillRect(QRect(0, 0, 10000, 10000), Qt::black);
    painter.setViewport(m_xPos - 20, m_yPos - 20, width(), height());

    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    QVector<SourceCodeView::SourceCodeBlockVecPtr>& sourceCodeBlockVec = latestSourceCodeView->getSourceCodeBlockVec();

    for(uint32_t i = 0; i < sourceCodeBlockVec.size(); ++i)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[i];
        painter.translate(m_xTranslate, m_yTranslate);
        painter.save();

        uint32_t maxStageWidth = 0;
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            const SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->at(j);
            sourceCodeBlockPtr->draw(painter, fontMetrics);

            painter.translate(0, sourceCodeBlockPtr->getHeight() + 30);

            if(sourceCodeBlockPtr->getWidth() > maxStageWidth)
                maxStageWidth = sourceCodeBlockPtr->getWidth();
        }

        painter.restore();

        m_xTranslate = maxStageWidth + 30;
        m_yTranslate = 0;
    }

    painter.end();
}

void CodeRenderWindow::mouseMoveEvent(QMouseEvent* event)
{
    QOpenGLWidget::mousePressEvent(event);

    if(m_buttonState)
    {
        QPoint delta = m_startPos - event->pos();
        m_xPos += delta.x();
        m_yPos += delta.y();

        //std::cout << m_xPos << std::endl;
        //std::cout << m_yPos << std::endl << std::endl;

        repaint();
    }
}

void CodeRenderWindow::mousePressEvent(QMouseEvent* event)
{
    QOpenGLWidget::mousePressEvent(event);

    Qt::MouseButton button = event->button();
    if(button == Qt::LeftButton)
    {
        m_startPos = event->pos();
        m_buttonState = true;
    }

    setFocus();
}

void CodeRenderWindow::mouseReleaseEvent(QMouseEvent* event)
{
    QOpenGLWidget::mouseReleaseEvent(event);

    Qt::MouseButton button = event->button();
    if(button == Qt::LeftButton)
        m_buttonState = false;
}


void CodeRenderWindow::keyPressEvent(QKeyEvent* event)
{
    QOpenGLWidget::keyPressEvent(event);

    if(event->key() == Qt::Key_Up)
        m_yPos += 30;
    else if(event->key() == Qt::Key_Down)
        m_yPos -= 30;
    else if(event->key() == Qt::Key_Left)
        m_xPos += 30;
    else if(event->key() == Qt::Key_Right)
        m_xPos -= 30;
    else if(event->key() == Qt::Key_R)
    {
        m_xPos = 20;
        m_yPos = 20;
    }

    repaint();
}