#include <chrono>
#include <map>
#include <cmath>
#include <time.h>
#include <thread>

#include "manager.hpp"


//----------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
//#include <unistd.h>
#include <unistd.h>
//#include "mainwindow.cpp"
#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include "mouse.h"
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
using std::vector;
using namespace cv;
static Logger gLogger;

extern ting at;

int open_port1(void)
{
	int fd;
		
	fd=open("/dev/ttyTHS1",O_RDWR | O_NOCTTY | O_NONBLOCK);
	printf("fd=%d\n",fd);
	
	if(fd==-1)
	{
		perror("Can't Open SerialPort");
	}
	
	return fd;
}

int set_opt(int fd) 
{ 
     struct termios newtio,oldtio; 
/*保存测试现有串口参数设置，在这里如果串口号等出错，会有相关的出错信息*/ 
     if  ( tcgetattr( fd,&oldtio)  !=  0) {  
      perror("SetupSerial 1");
	printf("tcgetattr( fd,&oldtio) -> %d\n",tcgetattr( fd,&oldtio)); 
      return -1; 
     } 
     //fmemopen( &newtio, sizeof( newtio ) ); 
/*步骤一，设置字符大小*/ 
     newtio.c_cflag  |=  CLOCAL | CREAD;  
     newtio.c_cflag &= ~CSIZE;  
/*设置停止位*/ 
     newtio.c_cflag |= CS8; 
      
      
/*设置奇偶校验位*/ 
     //无奇偶校验位 
     newtio.c_cflag &= ~PARENB; 
   
     /*设置波特率*/ 

     cfsetispeed(&newtio, B115200); 
     cfsetospeed(&newtio, B115200); 
 
/*设置停止位*/ 
     
     newtio.c_cflag &=  ~CSTOPB; 
     
/*设置等待时间和最小接收字符*/ 
     newtio.c_cc[VTIME]  = 0; 
     newtio.c_cc[VMIN] = 0; 
/*处理未接收字符*/ 
     tcflush(fd,TCIFLUSH); 
/*激活新配置*/ 
if((tcsetattr(fd,TCSANOW,&newtio))!=0) 
     { 
      perror("com set error"); 
      return -1; 
     } 
     printf("set done!\n"); 
     return 0; 
} 



//stract



Trtyolosort::Trtyolosort(char *yolo_engine_path,char *sort_engine_path){
	sort_engine_path_ = sort_engine_path;
	yolo_engine_path_ = yolo_engine_path;
	//Ui::MainWindow *ui=nullptr;
	trt_engine = yolov5_trt_create(yolo_engine_path_);
	printf("manager  86------------,,create yolov5-trt , instance = %p\n", trt_engine);
	DS = new DeepSort(sort_engine_path_, 128, 256, 0, &gLogger);
	
	
	//bool isColor=(img.type()==CV_8UC3);//判断相机(视频)是否为彩色
  

}

vector<thread> TrackerThread_;

vector<int> bboxxxx;
vector<Ptr<Tracker>> trackerCSRT;
vector<Rect2d> bboxCSRT;
vector<bool> OK_;


void CSRT_tracker1( vector<int>* bboxxxx,int i) {
    std::cout<<"250----------------------"<<i<<std::endl;

    (*bboxxxx)[i]=(i);
}

void CSRT_tracker(vector<Ptr<Tracker>>* tracker, Mat* frame, vector<Rect2d>* bbox, vector<bool>* ok_CSRT, int i) {
    (*ok_CSRT)[i] = (*tracker)[i]->update(*frame, (*bbox)[i]);
}
void CSRT_tracker_erase_(vector<Ptr<Tracker>>* tracker, vector<Rect2d>* bbox, vector<bool>* ok_CSRT, int i) {
    (*tracker).erase((*tracker).begin() + i);
    (*bbox).erase((*bbox).begin() + i);
    (*ok_CSRT).erase((*ok_CSRT).begin() + i);
    //(*Start_time_record).erase((*Start_time_record).begin() + i);


}
extern int ffl;
extern int zhui;
void Trtyolosort::creat(cv::Mat& frame){
    //0 1 forever ok,4     5deepbug  6none  7have but no show becaues update no ok
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

        bboxes[cou].x=ii.x;

        bboxes[cou].y=ii.y;
        bboxes[cou].width=ii.width-ii.x;
        bboxes[cou].height=ii.height-ii.y;

        cou=cou+1;
       }

    for (int kk =0;kk<bboxes.size();kk++)
    {
        bool OK_0 = false;

       Ptr<Tracker > tracker_0;
       //tracker_0 = TrackerCSRT::create();
       tracker_0 = TrackerKCF::create();


       bboxCSRT.push_back(bboxes[kk]);
       tracker_0->init(frame, bboxes[kk]);
       trackerCSRT.push_back(tracker_0);
       OK_.push_back(OK_0);
       //clock_t start_time = clock();
       //ptr_bboxCSRT.push_back(bboxes[kk]);
       //Start_time_record.push_back(start_time);
    }



    //sleep(3);
    jk.clear();
    std::vector<Result>().swap(jk);

    ffl=1;
    zhui=zhui+1;
    at.clear();
    std::vector<int>().swap(at);






}
void getRandomColors(vector<Scalar> &colors, int numColors)
{
        RNG rng(0);
        for (int i = 0; i < numColors; i++)
        {
                colors.push_back(Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
        }
}

cv::Mat Trtyolosort::upda(Ui::MainWindow *ui,cv::Mat& fram,int &ill){
    vector<Scalar> colors;

    if(ill==0){  //清空显示信息屏
        ui->listWidget_2->clear();
    }
    getRandomColors(colors,trackerCSRT.size());
    if(OK_.size() > 0){
        double timer = (double)getTickCount();
        for (int i = 0; i < trackerCSRT.size(); i++) {
            TrackerThread_.push_back(thread(CSRT_tracker, &trackerCSRT, &fram, &bboxCSRT, &OK_, i));
            //std::cout<<"361------------------\n"<<std::endl;
        } //for
        for (auto& ite : TrackerThread_) {
            ite.join();//等待县城end  bing  update
        }
        TrackerThread_.clear(); //vector<thread> TrackerThread_;
        float fps = getTickFrequency() / ((double)getTickCount() - timer);
        //Mat frameCSRT = fram.clone();
        string str;
        int io=0;
        for (int i = 0; i < trackerCSRT.size(); i++) {

            if (OK_[i])
               {
                rectangle(fram, bboxCSRT[i], colors[i], 2, 1);
                 if (ill%10==0){

                ui->listWidget_2->clear(); //------------
                //std::cout<<"379------------------\n"<<"i:"<<i<<std::endl;

                //imshow("CSRT Tracking", frameCSRT);
                for (int i = 0; i < trackerCSRT.size(); i++) {
                QString show_text00;
                show_text00=QString::fromLocal8Bit("auto--ID:");

                show_text00.append(QString::fromLocal8Bit("  x1:"));
                show_text00.append(QString::number(bboxCSRT[i].x));

                show_text00.append(QString::fromLocal8Bit("  y1:"));
                show_text00.append(QString::number(bboxCSRT[i].y));

                show_text00.append(QString::fromLocal8Bit("  x2:"));
                show_text00.append(QString::number(bboxCSRT[i].width+bboxCSRT[i].x));

                show_text00.append(QString::fromLocal8Bit("  y2:"));
                show_text00.append(QString::number(bboxCSRT[i].height+bboxCSRT[i].y));

                ui->listWidget_2->insertItem(io,show_text00);
                ui->listWidget_2->insertItem(io+1,"-----------------------------------------------------------------------------------------------------");
                io=io+2;
                }
                }//if
              }
            else {
                std::cout<<"383------------------\n"<<"i:"<<i<<std::endl;
                putText(fram, "Tracking failure detected" + to_string(i), Point(100, 80 + i * 10), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 255), 2);
                CSRT_tracker_erase_(&trackerCSRT, &bboxCSRT, &OK_, i);
                str = "Not , delete Rect!";
                }


            }
           putText(fram, "kcf Tracker Number:" + to_string(OK_.size()), Point(100, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);
           putText(fram, "FPS : " + to_string((int(fps))) + str, Point(100, 50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50, 170, 50), 2);



    }
    return fram;

}

//jiegouti ta Trtyolosort::showDetection(cv::Mat& img, std::vector<DetectBox>& boxes) {
jiegouti Trtyolosort::ta1 (cv::Mat& img, std::vector<DetectBox>& boxes,Ui::MainWindow *ui,int &ill) {


//cv::Mat Trtyolosort::showDetection(cv::Mat& img, std::vector<DetectBox>& boxes) {
    cv::Mat temp = img.clone();
    
    //auto start = std::chrono::system_clock::now();
    int FD;
    char buf[512];
    int len;
    FD = open_port1();
    set_opt(FD);
	
	clock_t start_draw,end_draw;
	double shijian;
	
	jiegouti fanhuibianl ;  //------------------------------------------------!!!!!!!!!!!!!!
	std::vector<jiegouti> jjgg;   //-------------!!!
	
	start_draw = clock();
	//item=ui->listWidget->currentItem();

    int df = 0;
    if(boxes.size()==0){
        ui->listWidget->clear();


    }


    for (auto box : boxes) {
        cv::Point lt(box.x1, box.y1);
        cv::Point br(box.x2, box.y2);
        cv::rectangle(temp, lt, br, cv::Scalar(255, 0, 0), 1);


        if (ill%10==0)
        {
         ui->listWidget->clear();

        //printf("%f manager38---\n",lt);
        //jiegouti fanhuibianl;
        printf("manager136---%f,%f,%f,%f ---\n",box.x1, box.y1,box.x2, box.y2);
        //QTextEdit->setText("122.43111");
        fanhuibianl.x1=box.x1;
        fanhuibianl.y1=box.y1;
        fanhuibianl.x2=box.x2;
        fanhuibianl.y2=box.y2;
        
        QString show_text0;
        show_text0=QString::fromLocal8Bit("ID:");
        show_text0.append(QString::number((int)box.trackID));
        
        //QString show_text1;
        show_text0.append(QString::fromLocal8Bit("  x1:"));
        show_text0.append(QString::number(box.x1));
        //show_text0.append(show_text1);
        //printf("manager146---\n");
        //ui->textEdit_2->setText(show_text1);
        
        
        
        //QString show_text2;
        show_text0.append(QString::fromLocal8Bit("  y1:"));
        show_text0.append(QString::number(box.y1));
        //show_text0.append(show_text2);
        //ui->listWidget->insertItem(0,show_text1);
        
        //QString show_text3;
        show_text0.append(QString::fromLocal8Bit("  x2:"));
        show_text0.append(QString::number(box.x2));
        //show_text0.append(show_text3);
        //ui->listWidget->insertItem(0,show_text1);
        
        //QString show_text4;
        show_text0.append(QString::fromLocal8Bit("  y2:"));
        show_text0.append(QString::number(box.y2));
        //show_text0.append(show_text4);
        
        ui->listWidget->insertItem(df,show_text0);
        //ui->listWidget->insertItem(0,show_text0);
        ui->listWidget->insertItem(df+1,"-----------------------------------------------------------------------------------------------------");
        
        
        //ui->listWidget->setFont(0,show_text1);
        df=df+2;
        //sprintf(buf,"--(%f,%f,%f,%f)\n",box.x1, box.y1,box.x2, box.y2);
        //len=strlen(buf);
        //printf("%d\n",len);
        write(FD,buf,52);
        //printf("122---%f,,%f,,%f,,%f\n",box.x1, box.y1,box.x2, box.y2);
        
        
        
        //printf("%f manager40---\n",box.x1);
        //cv::rectangle(temp, lt, br, cv::Scalar(255, 0, 0), 1);
        //std::string lbl = cv::format("ID:%d_C:%d_CONF:%.2f", (int)box.trackID, (int)box.classID, box.confidence);

		//std::string lbl = cv::format("ID:%d_C:%d", (int)box.trackID, "plane");
		//std::string lbl = cv::format("ID:%d_x:%f_y:%f",(int)box.trackID,(box.x1+box.x2)/2,(box.y1+box.y2)/2);

     }
        std::string lbl = cv::format("ID:%d_C:%d_plane", (int)box.trackID, (int)box.classID);
        cv::putText(temp, lbl, lt, cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0,255,0));

    }
    
    //auto end = std::chrono::system_clock::now();
	end_draw = clock();
	shijian=(double)(end_draw-start_draw)/CLOCKS_PER_SEC;
	printf("%f seconds157\n",shijian);
	
	//int delay_infer = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	//std::cout  << "manager,39,huakuang---:" << delay_infer << "ms" << std::endl;
	
	//-------------------------------------------------------------------------------------view
    //cv::imshow("img", temp);
    //cv::imwrite("_" + file_names[f - fcount + 1 + b], img);  //jiade
    
    
    //sprintf(buf,"181--(%f,%f,%f,%f)\n",box.x1, box.y1,box.x2, box.y2);
    //len=strlen(buf);
    //printf("%d\n",len);
    //write(FD,buf,43);
    //printf("184---%f,,%f,,%f,,%f\n",box.x1, box.y1,box.x2, box.y2);
    //writer.write(temp);//把图像写入视频流
    cv::waitKey(1);
    fanhuibianl.tupian=temp;
    return fanhuibianl;
}
//Ui::MainWindow *ui=nullptr;
//jiegouti ta Trtyolosort::TrtDetect(cv::Mat &frame,float &conf_thresh,std::vector<DetectBox> &det){


jiegouti Trtyolosort::ta2 (cv::Mat &frame,float &conf_thresh,std::vector<DetectBox> &det,Ui::MainWindow *ui,int &ill){

//cv::Mat Trtyolosort::TrtDetect(cv::Mat &frame,float &conf_thresh,std::vector<DetectBox> &det){

	// yolo detect
	printf("manager  183 \n");
	auto ret = yolov5_trt_detect(trt_engine, frame, conf_thresh,det);
	
	std::cout << "186det [" << std::endl;
    for (auto i : det)
       std::cout << i.x1 << ", ";
       //std::cout << i.y1 << ", ";
       //std::cout << i->x2 << ", ";
       //std::cout << i->y2 << ", ";
       //std::cout << i.confidence << ", ";
       //std::cout << i.classID << ", ";
       //td::cout << i.trackID << ", ";
    std::cout << "]" << endl;
    
	printf("manager  197,get..in.deep \n");
	DS->sort(frame,det);
	jiegouti temp2;
	
	//Ui::MainWindow *ui=nullptr;
        /*
        for (int i = 0; i < 6; i++) {
            bboxxxx.push_back(7);
            }
        for (int i = 0; i < 6; i++) {
            std::cout<<"280------------------"<<i<<std::endl;

            TrackerThread_.push_back(thread(CSRT_tracker1, &bboxxxx,  i));
            std::cout<<"283------------------"<<i<<std::endl;
        }
        for (auto& ite : TrackerThread_) {
            ite.join();//等待县城end  bing  update
        }
        std::cout << "270--------- [" << std::endl;
    for (auto iii : bboxxxx)
       std::cout << iii << ", ";
        std::cout << "]" << endl;
       //std::cout << i.y1 << ", ";
        //sleep(13);

	//temp2 and location
*/
	
        temp2 =ta1(frame,det,ui,ill);
	return temp2;
	
}


