#ifndef _MANAGER_H
#define _MANAGER_H

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "deepsort.h"
#include "logging.h"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "time.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "yolov5_lib.h"
#include "deepsort.h"
#include "/home/w/Desktop/all/src/ui_mainwindow.h"
using std::vector;
using namespace cv;
//static Logger gLogger;
typedef struct jiegouti
    {
	   cv::Mat tupian;
	   float x1;
	   float y1;
	   float x2;
	   float y2;
	
	
    }jiegouti;
//Ui::MainWindow *uiptr=nullptr;
class Trtyolosort{
public:
	// init 
	

	//void *uiinit(Ui::MainWindow *uiptr);
	Trtyolosort(char *yolo_engine_path,char *sort_engine_path);
	// detect and show
        jiegouti ta2(cv::Mat &frame,float &conf_thresh,std::vector<DetectBox> &det,Ui::MainWindow *ui,int &ill);
        jiegouti ta1(cv::Mat& img, std::vector<DetectBox>& boxes,Ui::MainWindow *ui,int &ill);
	//cv::Mat TrtDetect(cv::Mat &frame,float &conf_thresh,std::vector<DetectBox> &det);
	//cv::Mat showDetection(cv::Mat& img, std::vector<DetectBox>& boxes);
        cv::Mat upda(Ui::MainWindow *ui,cv::Mat &fram,int &ill);
        void creat(cv::Mat &fram);

private:
	char* yolo_engine_path_ = NULL;
	char* sort_engine_path_ = NULL;
    void *trt_engine = NULL;
    // deepsort parms
    DeepSort* DS;
    std::vector<DetectBox> t;
    //std::vector<DetectBox> det;
};
#endif  // _MANAGER_H

