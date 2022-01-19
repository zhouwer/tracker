#include "mouse.h"
//#include "date.h"
#include <QObject>
#include<QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <iostream>
#include<QLabel>
#include <unistd.h>
#include "mainwindow.h"
//MainWindow * MainWindow::myMainWindowtw = nullptr;
Mouse::Mouse(QWidget *parent) : QLabel(parent)
//Mouse::Mouse()
{
//Q_OBJECT
    //myMainWindowtw=this;
    //Ui::MainWindow *ui = MainWindow::myMainWindowtw->ui;

}


Result aa;
//Rect aa;
//Rect2d aaa;
boundingBoxes jk;
//extern Result aa;
//extern boundingBoxes jk;
//boundingBoxes jk;
//鼠标按下
//double xx=double(640)/double(1902);
//double yy=double(480)/double(1272); 4451

//double xx=1;
//double yy=1;
int bala=1;
extern ting at;
extern int ffl;
double xx=double(1900)/double(1902);
double yy=double(946)/double(1272);
void Mouse::mousePressEvent(QMouseEvent *ev)
{
    //当鼠标左键按下  提示信息
    if( ev->button() ==  Qt::LeftButton)
    {
        m_isMousePress = true;

        at.push_back(bala);




      //获取点坐标
        m_beginPoint = ev->pos();
        qDebug()<<"01"<<int(m_beginPoint.x()*xx);
        qDebug()<<"02"<<int(m_beginPoint.y()*yy);
        aa.x=int(m_beginPoint.x()*xx);
        aa.y=int(m_beginPoint.y()*yy);
        //qDebug()<<"02"<<aa.y;
        //printf("77\n");
        //update();
        //sleep(3);
        //int ting =1;

    }
}

//Ui::MainWindow *ui = MainWindow::myMainWindow->ui;
//鼠标释放
void Mouse::mouseReleaseEvent(QMouseEvent *ev)

{

    //Ui::MainWindow *ui = MainWindow::myMainWindowtw->ui;
    if(ev->button()==Qt::LeftButton)
    {
        m_endPoint = ev->pos();
        m_isMousePress = false;
        qDebug()<<"03"<<m_endPoint.x()*xx;
        qDebug()<<"04"<<m_endPoint.y()*yy;

        aa.width=m_endPoint.x()*xx;
        aa.height=m_endPoint.y()*yy;
        //qDebug()<<"05"<<aa.y;
        jk.push_back(aa);
        //for (auto i : jk)
        //std::cout << aa.x<< ", ";
        //std::cout << aa.y<< ", ";
        //ui->listWidget_2->insertItem(0,aa.x);

        //std::cout << "]" << endl;
        update();
        ffl=0;
        //at.clear();//-----------
    }


}
//鼠标移动，更新矩形框
void Mouse::mouseMoveEvent(QMouseEvent *ev)
{
    if( ev->buttons() &   Qt::LeftButton )
    {
        m_midPoint=ev->pos();
        update();
    }
}


//画矩形框


void Mouse::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);//先调用父类的paintEvent为了显示'背景'!!!
//    qDebug()<<"开始画";
//    qDebug()<<m_beginPoint;
//    qDebug()<<m_endPoint;
    QPainter m_painter(this);


    m_painter.setPen(QPen(Qt::red,2));




//    //设置画刷
//    QBrush brush(Qt::red);
//    //设置画刷风格
//    brush.setStyle(Qt::Dense7Pattern);
//    //让画家使用画刷
//    m_painter.setBrush(brush);
    //m_painter.drawRect(QRect(m_beginPoint,m_endPoint));
    if(!at.empty()){
    if (m_isMousePress)
    {
        m_painter.drawRect(QRect(m_beginPoint,m_midPoint));
    }
    else
    {
       m_painter.drawRect(QRect(m_beginPoint,m_endPoint));
    }
    }


}
//Ui::MainWindow *ui = MainWindow::myMainWindowtw->ui;
void Mouse::uuii(){
//ui->listWidget_2->insertItem(0,"ll");


}
