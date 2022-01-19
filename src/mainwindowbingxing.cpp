#include "mainwindow.h"
#include "stdlib.h"
#include "mouse.h"
//#include "precomp.hpp"
#include <opencv2/imgproc.hpp>
#include <algorithm>
//#include "selectROI.h"
#include <typeinfo>
#include "ui_mainwindow.h"
#include "manager.hpp"
//#include "manager.cpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
//#import<opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <chrono>
#include <map>
#include <cmath>
#include <time.h>
#include <unistd.h>
//#include <roi.h>     //------------------------------------------------------------------------------
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
//#include <algorithm>
#include <iostream>
//#include "date.h"

#include "mouse.h"
using namespace cv;
using namespace std;


//extern Result aa;
//extern boundingBoxes jk;
typedef struct jiegou
    {
           cv::Mat tupian;
           float x1;
           float y1;
           float x2;
           float y2;


    }jiegou;
MainWindow * MainWindow::myMainWindow = nullptr;
MainWindow * MainWindow::myMainWindowtw = nullptr;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setObjectName("hh");
    //this->setStyleSheet("#hh{border-image:url(/home/w/Desktop/all/src/13.jpeg);}"); //--------yi ge but  have   koong

    setWindowTitle("追踪程序");
    //setStyleSheet("border-image:url(:/home/w/Desktop/all/src/11.png);");
    //setStyleSheet("border-image:url(/home/w/Desktop/all/src/15.jpeg);");    //------------- mei ge all is  no kong badao
    //setStyleSheet("border-image:url(:/11.png);");
    //setStyleSheet("border-image:url(:/11.jpg);");


    //QPalette pal=this->palette();
   // pal.setBrush(QPalette::Background,QBrush( QPixmap (":/11.jpg")));
    // pal.setBrush(QPalette::Background,QBrush( QPixmap (":/11.png")));
     // pal.setBrush(QPalette::Background,QBrush( QPixmap (":/home/w/Desktop/all/src/11.png")));
       //pal.setBrush(QPalette::Background,QBrush( QPixmap ("/home/w/Desktop/all/src/11.jpg")));
    //setPalette(pal);

    QPixmap pix;

    pix=QPixmap("/home/w/Desktop/all/src/19.jpeg");

    ui->label->setPixmap(pix);

    QPixmap pix2;

    pix2=QPixmap("/home/w/Desktop/all/src/11.jpg");
    QPalette palette1;
    palette1.setColor(QPalette::Background, QColor(11, 222, 222));//rgb
     ui->label_2->setAutoFillBackground(true);  //一定要这句，否则不行
     ui->label_2->setPalette(palette1);
     ui->label_3->setAutoFillBackground(true);  //一定要这句，否则不行
     ui->label_3->setPalette(palette1);
     ui->label_4->setAutoFillBackground(true);  //一定要这句，否则不行
     ui->label_4->setPalette(palette1);


   // ui->label_2->setPixmap(pix2);
   // ui->label_3->setPixmap(pix2);
    //ui->label_4->setPixmap(pix2);
    ui->listWidget->setAutoFillBackground(true);
    ui->listWidget_2->setAutoFillBackground(true);
    ui->listWidget->setStyleSheet("border-image:url(/home/w/Desktop/all/src/16.jpeg);");
    //ui->listWidget_2->setStyleSheet("background-color:transparent;");
    ui->listWidget_2->setStyleSheet("border-image:url(/home/w/Desktop/all/src/20.jpg);");

    //QPalette p;
    //p =  ui->listWidget->palette();
    //p->setColor(listWidget.backgroundRole(), QColor("#424242"));
    //listWidget.setPalette(p);
    QPixmap pix3;

    pix3=QPixmap("/home/w/Desktop/all/src/17.jpeg");

    //ui->listWidget_2->setPixmap(pix3);
    ui->openButton->setAutoFillBackground(true);
    ui->endButton_2->setAutoFillBackground(true);
    ui->openButton->setStyleSheet("background-color:rgb(2,236,222)");
    ui->endButton_2->setStyleSheet("background-color:rgb(2,236,234)");


    myMainWindowtw=this;
    ui->label->setScaledContents(true);// 图片自适应窗口控件大小1
    setWindowState(Qt::WindowMaximized);
    Mouse m;
    m.uuii();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}


QImage MainWindow::Mat2QImage(cv::Mat cvImg)
{
    QImage qImg;
    cv::cvtColor(cvImg,cvImg,cv::COLOR_BGR2RGB);
    qImg=QImage((const unsigned char*)(cvImg.data),
                             cvImg.cols,cvImg.rows,          //宽，高
                             cvImg.step,                     //步长
                             QImage::Format_RGB888);         //24位图，RGB=[0,1,2]
    //return qImg.rgbSwapped();
    return qImg;
}
vector<string> trackerTypes = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};

/**
 * @brief Create a Tracker By Name object 根据设定的类型初始化跟踪器
 *
 * @param trackerType
 * @return Ptr<Tracker>
 */
ting at;
int ffl=1;
int ffll =1;
int zhui=0;

int uh=1;
Ptr<Tracker> createTrackerByName(string trackerType)
{
        Ptr<Tracker> tracker;
        if (trackerType == trackerTypes[0])
                tracker = TrackerBoosting::create();
        else if (trackerType == trackerTypes[1])
                tracker = TrackerMIL::create();
        else if (trackerType == trackerTypes[2])
                tracker = TrackerKCF::create();
        else if (trackerType == trackerTypes[3])
                tracker = TrackerTLD::create();
        else if (trackerType == trackerTypes[4])
                tracker = TrackerMedianFlow::create();
        else if (trackerType == trackerTypes[5])
                tracker = TrackerGOTURN::create();
        else if (trackerType == trackerTypes[6])
                tracker = TrackerMOSSE::create();
        else if (trackerType == trackerTypes[7])
                tracker = TrackerCSRT::create();
        else
        {
                cout << "Incorrect tracker name" << endl;
                cout << "Available trackers are: " << endl;
                for (vector<string>::iterator it = trackerTypes.begin(); it != trackerTypes.end(); ++it)
                {
                        std::cout << " " << *it << endl;
                }
        }
        return tracker;
}
void getRandomColors(vector<Scalar> &colors, int numColors)
{
        RNG rng(0);
        for (int i = 0; i < numColors; i++)
        {
                colors.push_back(Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
        }
}

int hj=0;
namespace
{//class MainWindow;
/*
class eee
{
    public:
    vector<Rect> bboxess;
    bboxess teee(boundingBoxes &jk){

        Rect sam;
        vector<Rect> bboxes;
        sam.x=0.0;
        sam.y=0.0;
        sam.width=0.0;
        sam.height=0.0;
        int cou=0;
        for(auto ii:jk)
            {


            bboxes.push_back(sam);
            std::cout<<"x:"<<ii.x<<"--y:"<<ii.y<<"--w:"<<ii.width<<"--h:"<<ii.height<<endl;
            //int uj =ii.h;
            //if(ii==jk.end();
            //boundingBoxes ok=boundingBoxes.back();
            printf("-----23--1----1-\n");
            bboxes[cou].x=ii.x;
            printf("-----55--1----1-\n");
            bboxes[cou].y=ii.y;
            bboxes[cou].width=ii.width-ii.x;
            bboxes[cou].height=ii.height-ii.y;
            printf("----44---1-%d---\n",cou);
            cou=cou+1;
           }
        bboxess hj =bboxes;
        return hj;


        }

    void select1(int &ffll,boundingBoxes &jk,std::vector<Rect> &yidui){

        for (;;)
        {
            bboxess yidui = teee(jk);
            //hj=hj+1;
            //printf("-----%d",hj);
            if (ffll == 0)


                break;

            //if (temp.width > 0 && temp.height > 0)
              //  boundingBoxes.push_back(temp);
              //  printf("164---%d",temp.x,"164\n");
        }
        ffll=1;


    }


};



*/

class ROISelector //:public QWidget
{
    //Q_OBJECT
  public:

    //Ui::MainWindow *ui;//=MainWindow::ui;
     //explicit ROISelector(QWidget *parent = nullptr);
     Ui::MainWindow *ui = MainWindow::myMainWindow->ui;



    Rect select(const String &windowName, Mat img, bool showCrossair = true, bool fromCenter = true)
    {
        // show notice to user
        //int key;
        printf("82-----137--Select a ROI and then press SPACE or ENTER button!\n");
        printf("83--2mm-Cancel the selection process by pressing c button!\n");
        printf("139!!!!!!!!!!!!\n");
        key = 0;
        printf("141!!!!!!!!!!!!");
        //ui->listWidget_2->insertItem(0,"aaa");
        imageSize = img.size();//640，480
        std::cout << "67dets [" << imageSize<<std::endl;
       // printf("143!!!!!!!!!!!!",imageSize);
        // set the drawing mode
        selectorParams.drawFromCenter = fromCenter;
        printf("145!!!!!!!!!!!!");
        // show the image and give feedback to user
        imshow(windowName, img);  //view tu no box----------huabushang--------------------------1111111111111111111111111

/*
        namedWindow(windowName.toStdString(), 1); // CV_WINDOW_NORMAL); // 0;
        HWND hwnd = (HWND)cvGetWindowHandle(windowName.toLatin1().data()); //toLatinl()转char*
        //取title窗体的父窗体句柄
        HWND hparent =::GetParent(hwnd);
        //改变某个子窗体的父窗口(子窗口句柄,新的父窗口句柄)
        ::SetParent(hwnd, (HWND)ui->label->winId());  //winId()取win32api要用的窗口句柄
        //显示窗体SW_SHOW  隐藏窗体SW_HIDE
        ::ShowWindow(hparent, SW_HIDE);
        imshow(windowName.toStdString(), src);
*/

        //*设置label图像
        //QImage* img = new QImage;

        //ui->label->setPixmap(QPixmap::fromImage(img));


        //cv::moveWindow(windowName,111,111);
        printf("148!!!!!!!!!!!!");
        //image =  Mat2QImagee(img);      //Mat->QImage
        QImage qImg;
        //cv::cvtColor(img,img,cv::COLOR_BGR2RGB);//--------------------------------------------------------
        qImg=QImage((const unsigned char*)(img.data),img.cols,img.rows, img.step,QImage::Format_RGB888);
        printf("153!!!!!!!!!!!!");
        //ui->label->setPixmap(QPixmap());
        //const capture.read(frame)==false ;
        ui->label->setPixmap(QPixmap::fromImage((qImg)));
        printf("155!!!!!!!!!!!!");
        // copy the data, rectangle should be drawn in the fresh image
        selectorParams.image = img.clone();

        // select the object
        //setMouseCallback(windowName, mouseHandler, (void*)this);
        setMouseCallback(windowName, mouseHandler, (void*)this);

        // end selection process on SPACE (32) ESC (27) or ENTER (13)
        while (!(key == 32 || key == 27 || key == 13))
        {
            // draw the selected object
            rectangle(selectorParams.image, selectorParams.box, Scalar(255, 0, 0), 2, 1);
            //printf("105--!\n",selectorParams.box.x);  si xunhuan?
            //printf("106--!\n",selectorParams.box.y);
            // draw cross air in the middle of bounding box

            if (showCrossair)
            {
                // horizontal line
                line(selectorParams.image,
                     Point((int)selectorParams.box.x,
                           (int)(selectorParams.box.y + selectorParams.box.height / 2)),
                     Point((int)(selectorParams.box.x + selectorParams.box.width),
                           (int)(selectorParams.box.y + selectorParams.box.height / 2)),
                     Scalar(255, 0, 0), 2, 1);

                // vertical line
                line(selectorParams.image,
                     Point((int)(selectorParams.box.x + selectorParams.box.width / 2),
                           (int)selectorParams.box.y),
                     Point((int)(selectorParams.box.x + selectorParams.box.width / 2),
                           (int)(selectorParams.box.y + selectorParams.box.height)),
                     Scalar(255, 0, 0), 2, 1);
            }

            // show the image bounding box
            imshow(windowName, selectorParams.image);//-----------以画，展示出来-----------------------------------------------------222222222222222222
            QImage qImg;
            cv::cvtColor(selectorParams.image,selectorParams.image,cv::COLOR_BGR2RGB);
            qImg=QImage((const unsigned char*)(selectorParams.image.data),selectorParams.image.cols,selectorParams.image.rows, selectorParams.image.step,QImage::Format_RGB888);


            //cv::cvtColor(selectorParams.image,selectorParams.image,cv::COLOR_BGR2RGB);
            //qImg=QImage((const unsigned char*)(selectorParams.image.data),selectorParams.image.cols,selectorParams.image.rows,         selectorParams.image.step,               QImage::Format_RGB888);

            ui->label->setPixmap(QPixmap::fromImage((qImg)));
            //image = Mat2QImagee(selectorParams.image);      //Mat->QImage
            //ui->label_2->setPixmap(QPixmap::fromImage((qImg)));


            // reset the image
            selectorParams.image = img.clone();

            // get keyboard event
            key = waitKey(30);

            if (key == 'c' || key == 'C')//cancel selection
            {
                selectorParams.box = Rect();
                break;
            }
        }
        //cv::destroyWindow(windowName);
        //cleanup callback
        setMouseCallback(windowName, emptyMouseHandler, NULL);
        cv::destroyWindow(windowName);//--------------------------------------------------------------------------------------

        return selectorParams.box;
    }

    void select(const String &windowName, Mat img, std::vector<Rect> &boundingBoxes,
                bool showCrosshair = true, bool fromCenter = true)
    {
        printf("152---Finish the selection process by pressing ESC button!\n");
        boundingBoxes.clear();
        key = 0;

        // while key is not ESC (27)
        for (;;)
        {
            Rect temp = select(windowName, img, showCrosshair, fromCenter);
            if (key == 27)
                break;
            if (temp.width > 0 && temp.height > 0)
                boundingBoxes.push_back(temp);
                printf("164---%d",temp.x,"164\n");
        }
    }

    struct handlerT
    {
        // basic parameters
        bool isDrawing;
        Rect2d box;
        Mat image;
        Point2f startPos;

        // parameters for drawing from the center
        bool drawFromCenter;

        // initializer list
        handlerT() : isDrawing(false), drawFromCenter(true){};
    } selectorParams;
  private:
    static void emptyMouseHandler(int, int, int, int, void*)
    {
    }

    static void mouseHandler(int event, int x, int y, int flags, void *param)
    {
        ROISelector *self = static_cast<ROISelector *>(param);
        self->opencv_mouse_callback(event, x, y, flags);
    }

    void opencv_mouse_callback(int event, int x, int y, int)
    {
        switch (event)
        {
        // update the selected bounding box
        case EVENT_MOUSEMOVE:
            if (selectorParams.isDrawing)
            {
                if (selectorParams.drawFromCenter)
                {
                    // limit half extends to imageSize
                    float halfWidth = std::min(std::min(
                            std::abs(x - selectorParams.startPos.x),
                            selectorParams.startPos.x),
                            imageSize.width - selectorParams.startPos.x);
                    float halfHeight = std::min(std::min(
                            std::abs(y - selectorParams.startPos.y),
                            selectorParams.startPos.y),
                            imageSize.height - selectorParams.startPos.y);

                    selectorParams.box.width = halfWidth * 2;
                    selectorParams.box.height = halfHeight * 2;
                    selectorParams.box.x = selectorParams.startPos.x - halfWidth;
                    selectorParams.box.y = selectorParams.startPos.y - halfHeight;

                }
                else
                {
                    // limit x and y to imageSize
                    int lx = std::min(std::max(x, 0), imageSize.width);
                    int by = std::min(std::max(y, 0), imageSize.height);
                    selectorParams.box.width = std::abs(lx - selectorParams.startPos.x);
                    selectorParams.box.height = std::abs(by - selectorParams.startPos.y);
                    selectorParams.box.x = std::min((float)lx, selectorParams.startPos.x);
                    selectorParams.box.y = std::min((float)by, selectorParams.startPos.y);
                }
            }
            break;

        // start to select the bounding box
        case EVENT_LBUTTONDOWN:
            selectorParams.isDrawing = true;
            selectorParams.box = Rect2d(x, y, 0, 0);
            selectorParams.startPos = Point2f((float)x, (float)y);
            break;

        // cleaning up the selected bounding box
        case EVENT_LBUTTONUP:
            selectorParams.isDrawing = false;
            if (selectorParams.box.width < 0)
            {
                selectorParams.box.x += selectorParams.box.width;
                selectorParams.box.width *= -1;
            }
            if (selectorParams.box.height < 0)
            {
                selectorParams.box.y += selectorParams.box.height;
                selectorParams.box.height *= -1;
            }
            break;
        }
    }

    // save the keypressed character
    int key;
    Size imageSize;
};
}



void cv::selectROIs(const String& windowName, InputArray img,
                             std::vector<Rect>& boundingBox, bool showCrosshair, bool fromCenter)
{
    ROISelector selector;
    selector.select(windowName, img.getMat(), boundingBox, showCrosshair, fromCenter);
    
}




void MainWindow::on_openButton_clicked()
{



    vector<int> re;

    map<int,vector<int>> personstate;
    map<int,int> classidmap;
    bool is_first = true;
    char* yolo_engine = (char*)"/home/w/Desktop/all/src/lastt.engine";
    //char* yolo_engine = (char*)"/home/w/c--/yolov5-deepsort-tensorrt/resources/yolov5s.engine";
    char* sort_engine = (char*)"/home/w/Desktop/all/src/deepsort.engine";
    //char* yolo_engine = "";
    //char* sort_engine = "";
    float conf_thre = 0.1;
    Trtyolosort yosort(yolo_engine,sort_engine);

    //VideoCapture capture;
    //VideoWriter  writer;
    cv::Mat frame;
    cv::Mat frame2;
    cv::Mat frame3;
    jiegouti frame1;
    //double x1, y1,x2, y2;
    //frame = capture.open(0);


    //frame = capture.open("/home/w/Desktop/all/src/1.mp4");
    //capture.read(frame);

    capture.open("/home/w/Desktop/all/src/1.mp4");
    //capture.open("/home/w/Desktop/all/无人机航拍/安义.mp4");
    //capture.open("/home/w/Desktop/all/无人机航拍/昌航.mp4");
    //capture.open("/home/w/Desktop/all/无人机航拍/天津/1026/右.mp4");
    //capture.open("/home/w/Desktop/all/无人机航拍/天津/1026/左.mp4");


    //VideoCapture capture("/home/w/Desktop/all/src/1.mp4");1
    capture >> frame;
    if (!capture.isOpened()){
        std::cout<<"can not open......."<<std::endl;
        //return -1 ;
    }


    //string trackerType = trackerTypes[7];
    Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();


    int coder=VideoWriter::fourcc('M','J','P','G');//选择编码格式
    //int coder=VideoWriter::fourcc('M', 'P', '4', 'V') ;//选择编码格式

    double fps=20.0;//设置视频帧率
    //string filename="live.mp4";//保存的视频文件名称
    string filename="live.avi";//保存的视频文件名称

    //std::cout  << "117----" << frame.size()<< std::endl;
    //sleep(3);
    writer.open(filename,coder,fps,frame.size(), true);//创建保存视频文件的视频流





    std::vector<DetectBox> det;
    auto start_draw_time = std::chrono::system_clock::now();

    clock_t start_draw,end_draw;
    start_draw = clock();
    int ill = 0;
    //int key;
    char biao =0;
    char flagg =0;
    std::cout  << "at.empty()-------:" << at.empty() << ".." << std::endl;
   // sleep(3);
    //at.clear();
    extern boundingBoxes jk;
    int yici=0;
    jiegou ee;
    cv::Mat ffr;

    //while(capture.read(frame)){
      while(1){



      if(!at.empty()){



           printf("----%d",ill);

          }


       else
           {
        capture>>frame;
        }
      std::cout<<"origin img size:"<<frame.size()<<std::endl;
      //sleep(3);




        if (ill>=0 ){
         //vector<Rect> bboxesss;
         cv::resize(frame,frame3,Size(1900,946),0,0,INTER_AREA);
         //cv::resize(frame,frame3,Size(640,480),0,0,INTER_AREA);
         //cv::resize(frame,frame3,Size(720,720),0,0,INTER_AREA);
         //frame=frame3;

        // frame2=frame.clone();
         //frame2=frame;
         std::cout<<"origin img size:"<<frame3.size()<<std::endl;
         //sleep(3);
         auto start = std::chrono::system_clock::now();








        printf("mainwindow133.di.%d zhen****************************************************************************************************************\n",ill);
        //std::cout<<" img size:"<<frame.cols<<" "<<frame.rows<<std::endl;





        //auto start = std::chrono::system_clock::now();
        //cv::Mat frame1;
        frame1 = yosort.ta2(frame3,conf_thre,det,ui,ill);////////////////////////////////////
        //printf("%f,%f,%f,%f manager-------------------------------------------------------------------------------------------\n",det.x1, det.y1,det.x2, det.y2);
        //printf("%f,%f,%f,%f manager-------------------------------------------------------------------------------------------\n",det.x1, det.y1,det.x2, det.y2);
        //std::cout  << "143--------------det:" << det << "fps" << std::endl;


        //auto end = std::chrono::system_clock::now();
        //int delay_infer = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        //std::cout  << "485-------------zong fps:" << 1000/delay_infer << "fps" << std::endl;
        //std::cout  << "486--------------zong ms:" << delay_infer << "ms" << std::endl;
        //std::cout  << "49----" << frame1.size()<< std::endl;

        //}
        cv::Mat fram = frame1.tupian.clone();


       /* while(!at.empty()){
            //uh=uh+1;
            cv::Mat fram = frame1.tupian.clone();
            hanshu(ffll,boundingBoxes &jk, std::vector<Rect> &yidui);


            at.clear();


            std::cout  << "521----" << uh<< std::endl;

            //continue;
            //sleep(3);
       }
       */
       //ffll=1;
       //continue;  // big  while
        std::cout  << "631----" <<  std::endl;


        if(!at.empty()&yici==0){
            yici=yici+1;
            //printf("634-------------------------%d---/n",yici);
            std::cout  << "636----" << yici<< std::endl;
            //sleep(3);

            std::cout  << "631----\n" << ee.x1<< std::endl;
            //sleep(3);

            ee.tupian=fram.clone();
            ee.x1=1;

            //ffr=fram.clone();
            //imshow("ss",ee.tupian);





        }


        if(ffl==0){
            string trackerType = trackerTypes[2];//0 1 forever ok,4     5deepbug  6none  7have but no show becaues update no ok
            vector<Rect> bboxes;  //
            extern boundingBoxes jk;
            Rect sam;
            sam.x=0.0;
            sam.y=0.0;
            sam.width=0.0;
            sam.height=0.0;
            int cou=0;
            for(auto ii:jk)
                {


                bboxes.push_back(sam);
                std::cout<<"x:"<<ii.x<<"--y:"<<ii.y<<"--w:"<<ii.width<<"--h:"<<ii.height<<endl;
                //int uj =ii.h;
                //if(ii==jk.end();
                //boundingBoxes ok=boundingBoxes.back();
                //printf("-----23--1----1-\n");
                bboxes[cou].x=ii.x;
                //printf("-----55--1----1-\n");
                bboxes[cou].y=ii.y;
                bboxes[cou].width=ii.width-ii.x;
                bboxes[cou].height=ii.height-ii.y;
                //printf("----44---1-%d---\n",cou);
                cou=cou+1;
               }
           // imshow("ss",ee.tupian);

            for (int i = 0; i < bboxes.size(); i++)
            {
                //std::cout<<"xx:"<<bboxes[i].x<<"--yy:"<<bboxes[i].y<<"--ww:"<<bboxes[i].width<<"--hh:"<<bboxes[i].height<<endl;
                multiTracker->add(createTrackerByName(trackerType), fram, Rect2d(bboxes[i]));
            }
            //sleep(3);
            jk.clear();
            std::vector<Result>().swap(jk);
            ffl=1;
            zhui=zhui+1;
            at.clear();
            std::vector<int>().swap(at);
            yici=0;


        }

/*
        if(ffl==0){



            //Ptr<MultiTracker> multiTracker = cv::MultiTracker::create();
            //vector<string> trackerTypes = {"BOOSTING", "MIL", "KCF", "TLD", "MEDIANFLOW", "GOTURN", "MOSSE", "CSRT"};
            string trackerType = trackerTypes[2];//0 1 forever ok,4     5deepbug  6none  7have but no show becaues update no ok
            vector<Rect> bboxes;  //                    2 good,3 no ,


            //Rect bboxes;


            cv::Mat fram = frame1.tupian.clone();
            hanshu(ffll,boundingBoxes &jk, std::vector<Rect> &bboxes);


            at.clear();


            printf("522\n");

            //extern std::vector<Result> boundingBoxes;
            //extern Result aa;
            //extern boundingBoxes jk;  /////////////////////-----------------------------------------------
            //printf("528\n");
            /*
            Rect sam;
            sam.x=0.0;
            sam.y=0.0;
            sam.width=0.0;
            sam.height=0.0;
            int cou=0;
            for(auto ii:jk)
                {


                bboxes.push_back(sam);
                std::cout<<"x:"<<ii.x<<"--y:"<<ii.y<<"--w:"<<ii.width<<"--h:"<<ii.height<<endl;
                //int uj =ii.h;
                //if(ii==jk.end();
                //boundingBoxes ok=boundingBoxes.back();
                printf("-----23--1----1-\n");
                bboxes[cou].x=ii.x;
                printf("-----55--1----1-\n");
                bboxes[cou].y=ii.y;
                bboxes[cou].width=ii.width-ii.x;
                bboxes[cou].height=ii.height-ii.y;
                printf("----44---1-%d---\n",cou);
                cou=cou+1;
               }

*/

        /*
            for (int i = 0; i < bboxes.size(); i++)
            {
                //std::cout<<"xx:"<<bboxes[i].x<<"--yy:"<<bboxes[i].y<<"--ww:"<<bboxes[i].width<<"--hh:"<<bboxes[i].height<<endl;
                multiTracker->add(createTrackerByName(trackerType), fram, Rect2d(bboxes[i]));
            }
            //sleep(3);
            jk.clear();
            std::vector<Result>().swap(jk);
            ffl=1;
            zhui=zhui+1;
            at.clear();
            std::vector<int>().swap(at);



         }*/



        if(zhui!=0){
        //int sizeee;
       //bool ok = multiTracker->update(frame);
        //for(unsigned i=0;i< multiTracker->trackerList.size(); i++){
        //  bool  ok = multiTracker->trackerList[i]->update(frame, multiTracker->objects[i]);
         // std::cout << "okkkkkkkkkkk=" <<ok<< endl;
       //s }
        //std::cout << "okkkkkkkkkkk=" <<multiTracker->trackerList.size()<< endl;
        //std::cout << "okkkkkkkkkkk=" <<tracker(0).size()<< endl;
       // sleep(10);
        vector<Scalar> colors;
            //bboxesss.clear();
        if(ill==0){
            ui->listWidget_2->clear();
        }
        //ui->listWidget_2->clear(); /


        getRandomColors(colors, multiTracker->getObjects().size());
        //ui->listWidget_2->clear(); //------------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        int zz=30;
        //list[];
        int iooo=0;
        for(unsigned idv=0;idv< multiTracker->trackerList.size(); idv++){
            vector<int>::iterator it = std::find(re.begin(),re.end(),idv);
            if(!(it!=re.end())){

            bool  ok = multiTracker->trackerList[idv]->update(fram, multiTracker->objects[idv]);

            int io=0;



            if (ok == true)


                {
                rectangle(fram, multiTracker->getObjects()[idv], colors[idv], 2, 1);
                //sleep(3);


                if (ill%10==0)

                     {

                                 ui->listWidget_2->clear(); //------------
                                 for(unsigned idvv=0;idvv< multiTracker->trackerList.size(); idvv++){
                                     if (multiTracker->trackerList[idvv]->update(fram, multiTracker->objects[idvv]) == true){



                                        QString show_text00;
                                        show_text00=QString::fromLocal8Bit("auto--ID:");

                                        show_text00.append(QString::fromLocal8Bit("  x1:"));
                                        show_text00.append(QString::number(multiTracker->getObjects()[idvv].x));

                                        show_text00.append(QString::fromLocal8Bit("  y1:"));
                                        show_text00.append(QString::number(multiTracker->getObjects()[idvv].y));

                                        show_text00.append(QString::fromLocal8Bit("  x2:"));
                                        show_text00.append(QString::number(multiTracker->getObjects()[idvv].width+multiTracker->getObjects()[idvv].x));

                                        show_text00.append(QString::fromLocal8Bit("  y2:"));
                                        show_text00.append(QString::number(multiTracker->getObjects()[idvv].height+multiTracker->getObjects()[idvv].y));

                                        ui->listWidget_2->insertItem(io,show_text00);
                                        ui->listWidget_2->insertItem(io+1,"-----------------------------------------------------------------------------------------------------");
                                        io=io+2;
                                        }
                                } // show
                } // update ==ok
                iooo=iooo+1;

            }

          else
                {
                    if(!(it!=re.end())){
                    re.push_back(idv);
                     }



                      //rectangle(frame, multiTracker->getObjects()[i], colors[i], 2, 1);
                }

           }


            //  in   re
          else
            { char text0[20] = {};

            sprintf(text0, "miss:%d", idv);


            putText(fram,text0,cvPoint(30,zz),FONT_HERSHEY_SIMPLEX,0.5, colors[idv]);
            zz=zz+20;
            if(idv+1== multiTracker->trackerList.size()&iooo==0){
                 ui->listWidget_2->clear();
            }
            }





        } // for tracker

     } //have
        

        







        image = Mat2QImage(fram);      //Mat->QImage

        if(at.empty()){

        ui->label->setPixmap(QPixmap::fromImage(image));   //QImage->QPixmap,并将图像显示在label上
        }





        writer.write(fram);


        std::cout  << "at.empty()----763---:" << at.empty() << ".." << std::endl;
        auto end = std::chrono::system_clock::now();
        int delay_infer = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout  << "897-------------zong fps:" << 1000/delay_infer << "fps" << std::endl;
        std::cout  << "898--------------zong ms:" << delay_infer << "ms" << std::endl;

        } //if i>0

        // ill++;



     //else run
        ill++;

    }//while








}
//显示下一帧图像
void MainWindow::nextFrame()
{
    capture >> frame;          //获取的图像frame是Mat数据矩阵
    image = Mat2QImage(frame);//Mat->QImage
    ui->label->setPixmap(QPixmap::fromImage(image));    //fromImage(image): QImage->QPixmap
                                                        //最后将 QPixmap 将图像显示在label上
}


//void MainWindow::on_pushButton_clicked(bool checked)
/*void MainWindow::on_pushButton_clicked()
{


        ffl=0;
        ffll=0;
        uh=505555;


}
*/
void MainWindow::on_endButton_2_clicked()
{



       //sleep(11111);
       capture.release();                //关闭摄像头
       writer.release();


       //ui->label->setPixmap(QPixmap());  //释放内存，关闭画面
       

}
