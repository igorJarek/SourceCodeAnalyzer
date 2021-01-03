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
    CodeRenderWindow(App& app, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent * event) override;

    void keyPressEvent(QKeyEvent* event) override;

private:
    QSharedPointer<SourceCodeView> m_sourceCodeView = nullptr;
    App&     m_app;

    bool     m_buttonState = false;
    QPoint   m_leftButtonMoveStartPos;

    uint32_t m_viewportPosX = 20;
    uint32_t m_viewportPosY = 20;

    double   m_zoom = 1.0;
};
