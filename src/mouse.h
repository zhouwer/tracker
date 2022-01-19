#ifndef MOUSE_H
#define MOUSE_H
//#include "date.h"
#include "mainwindow.h"
//#include "ui_mainwindow.h"  //-----------------------
#include <QLabel>
//#include <Q_OBJECT>
#include <QObject>
#include <QPainter>
#include <vector>
using namespace std;
//typedef Rect_<double> Rect2d;
typedef struct Result{
    int x;
    int y;
    int width;
    int height;
}Result;
typedef std::vector<Result> boundingBoxes;
//typedef std::vector<Rect> boundingBoxes;
//extern Result aa;
//extern boundingBoxes jk;
class Mouse : public QLabel
{
    Q_OBJECT
public:
    //static MainWindow *myMainWindowtw;
    //Ui::MainWindow *ui = MainWindow::myMainWindowtw->ui;  //no
    explicit Mouse(QWidget *parent = nullptr);


    //鼠标按下
    void mousePressEvent(QMouseEvent *ev);
    //void boxx();
    //Rect select();
    //boundingBoxes boxx();

    //鼠标释放
    void  mouseReleaseEvent(QMouseEvent *ev);
    void  uuii();

    //鼠标移动
    virtual void  mouseMoveEvent(QMouseEvent *ev);




    //绘图操作
    void paintEvent(QPaintEvent *event);

signals:
private:
    bool m_isMousePress;
    QPoint m_beginPoint, m_endPoint;
    QPoint m_midPoint;
    QPainter m_painter;
};
#endif // MOUSE_H
