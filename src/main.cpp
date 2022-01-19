

#include "mainwindow.h"
#include <QApplication>
#include <opencv2/opencv.hpp>



using namespace cv;


int main(int argc, char *argv[]){
	// calculate every person's (id,(up_num,down_num,average_x,average_y))
	VideoCapture capture;
        VideoWriter  writer;
	
	QApplication a(argc, argv);
    MainWindow w;
    w.setAutoFillBackground(true);
    //w.setPalette(QPalette(QColor(250,250,200)));
    QPalette Palette;
    //QPixmap pixmap(":/home/w/Desktop/all/src/11.png");
    QPixmap pixmap("/home/w/Desktop/all/src/13.jpeg");
    Palette.setBrush(QPalette::Window,QBrush(pixmap));
    w.setPalette(Palette);   //-----------------------------many no kong



    w.setWindowFlags(w.windowFlags()& ~Qt::WindowMaximizeButtonHint);
    w.setFixedSize(w.width(),w.height());




    //this->setStyleSheet("#MainWindow{border-image:url(:/home/w/Desktop/all/src/11.png)}");

    //w.setStyleSheet(" QFrame#myframe{border-image:url(11.png)}" );
    w.show();

    return a.exec();
    
    
    
	
}
