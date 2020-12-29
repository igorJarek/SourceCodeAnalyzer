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

    void keyPressEvent(QKeyEvent* event) override;
    //void wheelEvent(QWheelEvent * event) override;

private:
    App& m_app;

    QImage m_renderTarget;
    uint32_t m_xTranslate = 20;
    uint32_t m_yTranslate = 20;

    uint32_t m_xPos = 20;
    uint32_t m_yPos = 20;
    bool m_buttonState = false;
    QPoint m_startPos;
};
