#pragma once

#include "SourceCodeView.h"

#include <QOpenGLWidget>
#include <QScrollBar>
#include <QImage>

class App;

class CodeRenderWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    CodeRenderWindow(QSharedPointer<SourceCodeView> sourceCodeView, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent * event) override;

    void keyPressEvent(QKeyEvent* event) override;

private:
    QSharedPointer<SourceCodeView> m_sourceCodeView                = nullptr;

    QPoint                         m_viewportPos;
    double                         m_zoom                          = 1.0;

    bool                           m_leftMouseButtonState          = false;
    QPoint                         m_leftMouseButtonMovingStartPos;
    QPoint                         m_leftMouseButtonMovingDeltaPos;
};
