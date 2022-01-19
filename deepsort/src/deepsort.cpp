#include "deepsort.h"

DeepSort::DeepSort(std::string modelPath, int batchSize, int featureDim, int gpuID, ILogger* gLogger) {
	printf("inDeepSort::DeepSort  ... \n");
    this->gpuID = gpuID;
    this->enginePath = modelPath;
    this->batchSize = batchSize;
    this->featureDim = featureDim;
    this->imgShape = cv::Size(64, 128);
    this->maxBudget = 100;
    this->maxCosineDist = 0.2;
    this->gLogger = gLogger;
    init();
    printf("ouDeepSort::DeepSort  ... \n");
}

void DeepSort::init() {
	printf("inDeepSort::init  ... \n");
    objTracker = new tracker(maxCosineDist, maxBudget);
    featureExtractor = new FeatureTensor(batchSize, imgShape, featureDim, gpuID, gLogger);
    int ret = enginePath.find(".onnx");
    if (ret != -1)
        featureExtractor->loadOnnx(enginePath);
    else
        featureExtractor->loadEngine(enginePath);
    printf("ouDeepSort::init  ... \n");
}

DeepSort::~DeepSort() {
    delete objTracker;
}

void DeepSort::sort(cv::Mat& frame, vector<DetectBox>& dets) {
    // preprocess Mat -> DETECTION
    printf("inputDeepSort::sort11  ... \n");
    DETECTIONS detections;
    vector<CLSCONF> clsConf;
    
    for (DetectBox i : dets) {
        DETECTBOX box(i.x1, i.y1, i.x2-i.x1, i.y2-i.y1);
        DETECTION_ROW d;  // kuang  con  256  ()*2
        d.tlwh = box;
        d.confidence = i.confidence;
        detections.push_back(d);  //k  con 
        clsConf.push_back(CLSCONF((int)i.classID, i.confidence)); //wu trackid
    }
    result.clear();
    results.clear();
    if (detections.size() > 0) {
		std::cout << "50detections.size()" << detections.size()<<std::endl;
        DETECTIONSV2 detectionsv2 = make_pair(clsConf, detections); //two i.confidence
        sort(frame, detectionsv2);
    }
    // postprocess DETECTION -> Mat
    dets.clear();
    for (auto r : result) {
        DETECTBOX i = r.second;
        DetectBox b(i(0), i(1), i(2)+i(0), i(3)+i(1), 1.);
        b.trackID = (float)r.first;
        dets.push_back(b);
    }
    for (int i = 0; i < results.size(); ++i) {
        CLSCONF c = results[i].first;
        dets[i].classID = c.cls;
        dets[i].confidence = c.conf;
    }
    std::cout << "67dets [" << std::endl;
    for (auto i : dets)
       std::cout << i.classID<< ", ";
    std::cout << "]" << endl;
    std::cout << "71dets [" << std::endl;
    for (auto i : dets)
       std::cout << i.trackID<< ", ";
    std::cout << "]" << endl;
    printf("ouputDeepSort::sort11  ... \n");
}


void DeepSort::sort(cv::Mat& frame, DETECTIONS& detections) {
    printf("inputDeepSort::sort..detections1  ... \n");
    bool flag = featureExtractor->getRectsFeature(frame, detections);
    if (flag) {
        objTracker->predict();
        objTracker->update(detections);
        //result.clear();
        for (Track& track : objTracker->tracks) {
            if (!track.is_confirmed() || track.time_since_update > 1)
                continue;
            result.push_back(make_pair(track.track_id, track.to_tlwh()));
        }
    }
    printf("ouputDeepSort::sort..detections1  ... \n");
}

void DeepSort::sort(cv::Mat& frame, DETECTIONSV2& detectionsv2) {
    printf("inputDeepSort::sort..detections2  ... \n");
    std::vector<CLSCONF>& clsConf = detectionsv2.first;
    DETECTIONS& detections = detectionsv2.second;
    bool flag = featureExtractor->getRectsFeature(frame, detections);
    //printf(9199119191,flag);
    std::cout <<"101..deepsort.c...flag:" << flag<<  std::endl;

    if (flag) {
        objTracker->predict();
        objTracker->update(detectionsv2);
        result.clear();
        results.clear();
        for (Track& track : objTracker->tracks) {
			printf("101  ... \n");
            if (!track.is_confirmed() || track.time_since_update > 1)
                continue;
            result.push_back(make_pair(track.track_id, track.to_tlwh()));
            results.push_back(make_pair(CLSCONF(track.cls, track.conf) ,track.to_tlwh()));
        }
    }
    std::cout <<"116..result:[" << std::endl;
    // have  many  <int,DETECTBOX>
    for (auto i : result)
       std::cout << i.first<< ", ";
    std::cout << "]" << endl;
    std::cout <<"121..results:[" <<  std::endl;
    //// have  many  <CLSCONF class,DETECTBOX>
    for (auto i : results)
       std::cout << i.second<< ", ";
    std::cout << "]" << endl;
    printf("ouputDeepSort::sort..detections2  ... \n");
}

void DeepSort::sort(vector<DetectBox>& dets) {
    printf("inputDeepSort::sort..<DetectBox>& dets  ... \n");
    DETECTIONS detections;
    for (DetectBox i : dets) {
        DETECTBOX box(i.x1, i.y1, i.x2-i.x1, i.y2-i.y1);
        DETECTION_ROW d;
        d.tlwh = box;
        d.confidence = i.confidence;
        detections.push_back(d);
    }
    if (detections.size() > 0)
        sort(detections);
    dets.clear();
    for (auto r : result) {
        DETECTBOX i = r.second;
        DetectBox b(i(0), i(1), i(2), i(3), 1.);
        b.trackID = r.first;
        dets.push_back(b);
    }
    printf("ouputDeepSort::sort..<DetectBox>& dets  ... \n");
}

void DeepSort::sort(DETECTIONS& detections) {
	printf("inputDeepSort::sort..detections  ... \n");
    bool flag = featureExtractor->getRectsFeature(detections);
    if (flag) {
        objTracker->predict();
        objTracker->update(detections);
        result.clear();
        for (Track& track : objTracker->tracks) {
            if (!track.is_confirmed() || track.time_since_update > 1)
                continue;
            result.push_back(make_pair(track.track_id, track.to_tlwh()));
        }
    }
    printf("ouputDeepSort::sort..detections  ... \n");
}
