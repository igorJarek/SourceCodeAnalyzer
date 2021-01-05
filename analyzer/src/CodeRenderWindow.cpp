#include "CodeRenderWindow.h"
#include "SourceCodeBlock.h"
#include "App.h"

#include <QTextDocument>
#include <QMouseEvent>
#include <QPainter>

CodeRenderWindow::CodeRenderWindow(QSharedPointer<SourceCodeView> sourceCodeView, QWidget *parent) :
    m_sourceCodeView(sourceCodeView), QOpenGLWidget(parent)
{

}

void CodeRenderWindow::paintEvent(QPaintEvent* /* event */)
{
    QPainter painter(this);

    QPoint viewPos = m_viewportPos + m_leftMouseButtonMovingDeltaPos;
    painter.setViewport(viewPos.x(), viewPos.y(), width(), height());

    m_sourceCodeView->draw(painter, m_zoom);

    painter.end();
}

void CodeRenderWindow::mouseMoveEvent(QMouseEvent* event)
{
    QOpenGLWidget::mousePressEvent(event);

    if(m_leftMouseButtonState)
    {
        m_leftMouseButtonMovingDeltaPos = m_leftMouseButtonMovingStartPos - event->pos();

        repaint();
    }
}

void CodeRenderWindow::mousePressEvent(QMouseEvent* event)
{
    QOpenGLWidget::mousePressEvent(event);

    Qt::MouseButton button = event->button();
    if(button == Qt::LeftButton)
    {
        m_leftMouseButtonMovingStartPos = event->pos();

        m_leftMouseButtonState = true;
    }

    setFocus();
}

void CodeRenderWindow::mouseReleaseEvent(QMouseEvent* event)
{
    QOpenGLWidget::mouseReleaseEvent(event);

    Qt::MouseButton button = event->button();
    if(button == Qt::LeftButton)
    {
        m_leftMouseButtonState = false;

        m_viewportPos += m_leftMouseButtonMovingDeltaPos;

        m_leftMouseButtonMovingDeltaPos = QPoint(0, 0);

        repaint();
    }
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
        m_viewportPos += QPoint(0, 30);
    else if(event->key() == Qt::Key_Down)
        m_viewportPos -= QPoint(0, 30);
    else if(event->key() == Qt::Key_Left)
        m_viewportPos += QPoint(30, 0);
    else if(event->key() == Qt::Key_Right)
        m_viewportPos -= QPoint(30, 0);

    repaint();
}