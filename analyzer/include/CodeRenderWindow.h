#pragma once

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
    App& m_app;

    QImage   m_renderTarget;
    uint32_t m_translateX = 20;
    uint32_t m_translateY = 20;

    bool     m_buttonState = false;
    QPoint   m_leftButtonMoveStartPos;

    uint32_t m_viewportPosX = 20;
    uint32_t m_viewportPosY = 20;

    double   m_zoom = 1.0;
};
