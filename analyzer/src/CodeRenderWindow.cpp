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
    const uint16_t STAGE_X_GAP {40};
    const uint16_t STAGE_Y_GAP {20};

    // get stages info (max height stage, stages width and height)
    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    QVector<SourceCodeView::SourceCodeBlockVecPtr>& sourceCodeBlockVec = latestSourceCodeView->getSourceCodeBlockVec();

    uint64_t maxHeightStage {0};
    QVector<QPoint> stagesInfo(sourceCodeBlockVec.size());

    for(size_t stageListIndex {0}; stageListIndex < sourceCodeBlockVec.size(); ++stageListIndex)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[stageListIndex];
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            const SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->at(j);
            QPoint sourceCodeBlockSize = sourceCodeBlockPtr->getSize();

            stagesInfo[stageListIndex].setY( stagesInfo[stageListIndex].y() + sourceCodeBlockSize.y() + STAGE_Y_GAP);
            if(sourceCodeBlockSize.x() > stagesInfo[stageListIndex].x())
                stagesInfo[stageListIndex].setX(sourceCodeBlockSize.x());
        }

        stagesInfo[stageListIndex].setY( stagesInfo[stageListIndex].y() - STAGE_Y_GAP);

        if(stagesInfo[stageListIndex].y() > maxHeightStage)
            maxHeightStage = stagesInfo[stageListIndex].y();
    }

    // set initial positions
    uint64_t xPosition {0};
    for(size_t stageListIndex {0}; stageListIndex < sourceCodeBlockVec.size(); ++stageListIndex)
    {
        SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[stageListIndex];

        uint64_t yPosition = (maxHeightStage - stagesInfo[stageListIndex].y()) / 2;
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->operator[](j);
            sourceCodeBlockPtr->setWidth(stagesInfo[stageListIndex].x());
            sourceCodeBlockPtr->setPosition(xPosition, yPosition);
            yPosition += sourceCodeBlockPtr->getSize().y() + STAGE_Y_GAP;
        }

        xPosition += stagesInfo[stageListIndex].x() + STAGE_X_GAP;
    }

    /*
    * m_renderTarget(3000, 5000, QImage::Format_RGB32)
    * 
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

    painter.fillRect(QRect(0, 0, 10000, 10000), Qt::black);
    painter.setViewport(m_viewportPosX - 20, m_viewportPosY - 20, width(), height());
    painter.scale(m_zoom, m_zoom);

    QSharedPointer<SourceCodeView> latestSourceCodeView = m_app.getLastSourceCodeView();
    QVector<SourceCodeView::SourceCodeBlockVecPtr>& sourceCodeBlockVec = latestSourceCodeView->getSourceCodeBlockVec();

    for(uint32_t i = 0; i < sourceCodeBlockVec.size(); ++i)
    {
        const SourceCodeView::SourceCodeBlockVecPtr& vecPtr = sourceCodeBlockVec[i];
        for(uint32_t j = 0; j < vecPtr->size(); j++)
        {
            const SourceCodeView::SourceCodeBlockPtr& sourceCodeBlockPtr = vecPtr->at(j);

            painter.translate(sourceCodeBlockPtr->getPosition().x(), sourceCodeBlockPtr->getPosition().y());
            sourceCodeBlockPtr->draw(painter);
            painter.translate(-sourceCodeBlockPtr->getPosition().x(), -sourceCodeBlockPtr->getPosition().y());
        }
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