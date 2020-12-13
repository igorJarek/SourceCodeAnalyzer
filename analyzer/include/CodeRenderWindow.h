#pragma once

#include <QOpenGLWidget>
#include <QScrollBar>

class App;

class CodeRenderWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    CodeRenderWindow(App& app, QWidget *parent);

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent * event) override;

private:
    App& m_app;
};
