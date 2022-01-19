#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "date.h"

#include <QTimer>
#include <QPixmap>
#include <QDebug>
#include <QImage>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QtWidgets>
#include <QMainWindow>
//#include "mainwindow.cpp"
//#include "mouse.h"
//extern jk;
using namespace std;
//extern int ting;
typedef std::vector<int> ting;
//extern Result aa;
//extern boundingBoxes jk;
namespace Ui {
class MainWindow;
class ROISelector;
//class Mouse;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static MainWindow *myMainWindow;
    static MainWindow *myMainWindowtw;
    Ui::MainWindow *ui;
    QImage image;  
    //new ROISelector ();
    static void mouseHandler(int event, int x, int y, int flags, void *param);
    static void emptyMouseHandler(int, int, int, int, void*);
    void opencv_mouse_callback(int event, int x, int y, int);
    struct handlerT
    {
        // basic parameters
        bool isDrawing;
        cv::Rect2d box;
        cv::Mat image;
        cv::Point2f startPos;

        // parameters for drawing from the center
        bool drawFromCenter;

        // initializer list
        handlerT() : isDrawing(false), drawFromCenter(true){};
    } selectorParams;

private slots:
    void nextFrame();
    void on_openButton_clicked();
    //ROISelector* roi;



    void on_endButton_2_clicked();
    //void on_pushButton_clicked();

    //bool on_pushButton_clicked() ;

private:
    
    //ROISelector * proi;
    cv::VideoCapture capture;            //一个获取视频的抽象接口结构
    cv::VideoWriter  writer;  
    cv::Mat frame;                       //一帧图像
                          //一张图像
    QTimer *timer;                       //定时器用于定时取帧，隔一段时间获取图像。
    QImage Mat2QImage(cv::Mat cvImg);    //Mat->QImage的转化
    QTextEdit *textEdit; 
    struct jiegoutii
      {
	   cv::Mat tupian;
	   float x1;
	   float y1;
	   float x2;
	   float y2;
	
	
      };
//private:
   // static MainWindow *chuanlai;

};

#endif // MAINWINDOW_H
