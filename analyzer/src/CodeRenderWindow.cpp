#include <CodeRenderWindow.h>
#include <SourceCodeBlock.h>
#include <App.h>

#include <QTextDocument>
#include <QMouseEvent>
#include <QPainter>

#include <iostream>

CodeRenderWindow::CodeRenderWindow(App& app, QWidget *parent) :
    m_app(app), QOpenGLWidget(parent)
{

}

void CodeRenderWindow::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.fillRect(QRect(0, 0, 3000, 5000), QColor(30, 30, 30));
    painter.setViewport(m_viewportPosX - 20, m_viewportPosY - 20, width(), height());

    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    latestSourceCodeView->draw(painter, m_zoom);

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
        m_zoom += 0.05;
    else
        m_zoom -= 0.05;

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