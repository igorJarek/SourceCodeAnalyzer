#include <CodeRenderWindow.h>
#include <SourceCodeBlock.h>
#include <App.h>

#include <QTextDocument>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

CodeRenderWindow::CodeRenderWindow(App& app, QWidget *parent) :
    m_app(app), QOpenGLWidget(parent), m_renderTarget(3000, 5000, QImage::Format_RGB32)
{
    /*
    QPainter     painter(&m_renderTarget);
    QFont        font("JetBrains Mono", 10, 10);
    QFontMetrics fontMetrics(font);

    painter.setFont(font);
    painter.fillRect(QRect(0, 0, 3000, 5000), Qt::black);

    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    QVector<SourceCodeView::SourceCodeBlockVecPtr>& sourceCodeBlockVec = latestSourceCodeView->getSourceCodeBlockVec();

    for(uint32_t i = 0; i < sourceCodeBlockVec.size(); ++i)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[i];
        painter.translate(m_translateX, m_translateY);
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

        m_translateX = maxStageWidth + 30;
        m_translateY = 0;
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
    painter.setViewport(m_viewportPosX - 20, m_viewportPosY - 20, width(), height());

    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    QVector<SourceCodeView::SourceCodeBlockVecPtr>& sourceCodeBlockVec = latestSourceCodeView->getSourceCodeBlockVec();

    for(uint32_t i = 0; i < sourceCodeBlockVec.size(); ++i)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[i];
        painter.translate(m_translateX, m_translateY);
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

        m_translateX = maxStageWidth + 30;
        m_translateY = 0;
    }

    painter.end();
}

void CodeRenderWindow::mouseMoveEvent(QMouseEvent* event)
{
    QOpenGLWidget::mousePressEvent(event);

    if(m_buttonState)
    {
        QPoint delta = m_leftButtonMoveStartPos - event->pos();
        m_viewportPosX += delta.x();
        m_viewportPosY += delta.y();

        repaint();
    }
}

void CodeRenderWindow::mousePressEvent(QMouseEvent* event)
{
    QOpenGLWidget::mousePressEvent(event);

    Qt::MouseButton button = event->button();
    if(button == Qt::LeftButton)
    {
        m_leftButtonMoveStartPos = event->pos();
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

void CodeRenderWindow::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() > 0)
        m_zoom += 0.1;
    else
        m_zoom -= 0.1;

    repaint();
}

void CodeRenderWindow::keyPressEvent(QKeyEvent* event)
{
    QOpenGLWidget::keyPressEvent(event);

    if(event->key() == Qt::Key_Up)
        m_viewportPosY += 30;
    else if(event->key() == Qt::Key_Down)
        m_viewportPosY -= 30;
    else if(event->key() == Qt::Key_Left)
        m_viewportPosX += 30;
    else if(event->key() == Qt::Key_Right)
        m_viewportPosX -= 30;
    else if(event->key() == Qt::Key_R)
    {
        m_viewportPosX = 20;
        m_viewportPosY = 20;
    }

    repaint();
}