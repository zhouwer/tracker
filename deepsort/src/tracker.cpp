#include "tracker.h"
#include "nn_matching.h"
#include "linear_assignment.h"
using namespace std;

#define MY_inner_DEBUG
#ifdef MY_inner_DEBUG
#include <string>
#include <iostream>
#endif
using namespace std;
tracker::tracker(               /*NearNeighborDisMetric *metric, */
    float max_cosine_distance, int nn_budget,
    float max_iou_distance, int max_age, int n_init)
{
    printf("intracker::tracker---  ... \n");
    this->metric = new NearNeighborDisMetric(
        NearNeighborDisMetric::METRIC_TYPE::cosine, 
        max_cosine_distance, nn_budget);
    this->max_iou_distance = max_iou_distance;
    this->max_age = max_age;
    this->n_init = n_init;

    this->kf = new KkalmanFilter();
    this->tracks.clear();
    this->_next_idx = 1;
    printf("outracker::tracker---  ... \n");
}

void tracker::predict()
{
  printf("intracker::predict---  ... \n");
  for (Track & track:tracks) {
        track.predit(kf);
    }
  printf("outracker::predict---  ... \n");
}

void tracker::update(const DETECTIONS & detections)
{
    printf("intracker::update1---  ... \n");
    TRACHER_MATCHD res;
    _match(detections, res);

    vector < MATCH_DATA > &matches = res.matches;
    for (MATCH_DATA & data:matches) {
        int track_idx = data.first;
        int detection_idx = data.second;
        tracks[track_idx].update(this->kf, detections[detection_idx]);
    }
    vector < int >&unmatched_tracks = res.unmatched_tracks;
    for (int &track_idx:unmatched_tracks) {
        this->tracks[track_idx].mark_missed();
    }
    vector < int >&unmatched_detections = res.unmatched_detections;
    for (int &detection_idx:unmatched_detections) {
        this->_initiate_track(detections[detection_idx]);
    }
    vector < Track >::iterator it;
    for (it = tracks.begin(); it != tracks.end();) {
        if ((*it).is_deleted()) it = tracks.erase(it);
        else ++it;
    }
    vector < int >active_targets;
    vector < TRACKER_DATA > tid_features;
  for (Track & track:tracks) {
        if (track.is_confirmed() == false) continue;
        active_targets.push_back(track.track_id);
        tid_features.push_back(std::make_pair(track. track_id, track.features));
        FEATURESS t = FEATURESS(0, 256);
        track.features = t;
    }
    this->metric->partial_fit(tid_features, active_targets);
    printf("outracker::update1---  ... \n");
}

void tracker::update(const DETECTIONSV2 & detectionsv2)  //have  feature
{
    printf("intracker::update2---  ... \n");
    const vector<CLSCONF>& clsConf = detectionsv2.first;
    const DETECTIONS& detections = detectionsv2.second;
    TRACHER_MATCHD res; //struct 1:match,,2:untracks,,3:undetec
    _match(detections, res);

    vector < MATCH_DATA > &matches = res.matches;
  for (MATCH_DATA & data:matches) {
        int track_idx = data.first;
        int detection_idx = data.second;
        tracks[track_idx].update(this->kf, detections[detection_idx], clsConf[detection_idx]);
    }
    vector < int >&unmatched_tracks = res.unmatched_tracks;
  for (int &track_idx:unmatched_tracks) {
        this->tracks[track_idx].mark_missed();
    }
    vector < int >&unmatched_detections = res.unmatched_detections;
  for (int &detection_idx:unmatched_detections) {
        this->_initiate_track(detections[detection_idx], clsConf[detection_idx]);
    }
    vector < Track >::iterator it; //??
    for (it = tracks.begin(); it != tracks.end();) {
        if ((*it).is_deleted()) it = tracks.erase(it);
        else ++it;
    }
    vector < int >active_targets;
    vector < TRACKER_DATA > tid_features;
  for (Track & track:tracks) {
        if (track.is_confirmed() == false) continue;
        active_targets.push_back(track.track_id);
        tid_features.push_back(std::make_pair(track. track_id, track.features));
        FEATURESS t = FEATURESS(0, 256);
        track.features = t;
    }
    this->metric->partial_fit(tid_features, active_targets);
    printf("outracker::update2---  ... \n");
}

void tracker::_match(const DETECTIONS & detections, TRACHER_MATCHD & res) //row have feture,,struct(3)
{
    printf("intracker::_match--  ... \n");
    vector < int >confirmed_tracks;
    vector < int >unconfirmed_tracks;
    int idx = 0;
  for (Track & t:tracks) {
	    std::cout  << "124-----tracker.c--------t.is_confirmed():" << t.is_confirmed()<< "dd " << std::endl;

        if (t.is_confirmed()) confirmed_tracks.push_back(idx);
        else unconfirmed_tracks.push_back(idx);
        idx++;
    }
    std::cout << "confirmed_tracks [" << std::endl;
    for (auto i : confirmed_tracks)
       std::cout << i << ", ";
    std::cout << "]" <<std::endl;
	//std::cout  << "131-----tracker.c----unconfirmed_tracks:" << unconfirmed_tracks<< "dd " << std::endl;
    std::cout << "unconfirmed_tracks [" << std::endl;
    for (auto i : unconfirmed_tracks)
       std::cout << i << ", ";
    std::cout << "]138" <<std::endl;
    
    TRACHER_MATCHD matcha = linear_assignment::getInstance()-> matching_cascade(
        this, &tracker::gated_matric,
        this->metric->mating_threshold,
        this->max_age,
        this->tracks,
        detections,
        confirmed_tracks);
        //detections, row have feture,,struct(3)
    vector < int >iou_track_candidates;
    iou_track_candidates.assign(unconfirmed_tracks.begin(), unconfirmed_tracks.end());
    vector < int >::iterator it;
    for (it = matcha.unmatched_tracks.begin(); it != matcha.unmatched_tracks.end();) {
        int idx = *it;
        if (tracks[idx].time_since_update == 1) {       //push into unconfirmed
            iou_track_candidates.push_back(idx);
            it = matcha.unmatched_tracks.erase(it);
            continue;
        }
        ++it;
    }
    std::cout << "detections [" << std::endl;
    for (auto i : detections)
       std::cout << i.tlwh << ", ";
    std::cout << "]" <<std::endl;
    //std::cout  << "153----detections:" << detections<< "dd " << std::endl;
    std::cout << "iou_track_candidates [" << std::endl;
    for (auto i : iou_track_candidates)
       std::cout << i << ", ";
    std::cout << "]" <<std::endl;
    //std::cout  << "154-----iou_track_candidates:" << iou_track_candidates<< "dd " << std::endl;
    std::cout << "matcha.unmatched_detections [" << std::endl;
    for (auto i : matcha.unmatched_detections)
       std::cout << i << ", ";
    std::cout << "]" <<std::endl;
    //std::cout  << "155-----detections:" << matcha.unmatched_detections<< "dd " << std::endl;

    TRACHER_MATCHD matchb = linear_assignment::getInstance()->min_cost_matching(
        this, &tracker::iou_cost,
        this->max_iou_distance,
        this->tracks,
        detections,
        iou_track_candidates,
        //??????detections);
        matcha.unmatched_detections);
    //get result:
    res.matches.assign(matcha.matches.begin(), matcha.matches.end());
    res.matches.insert(res.matches.end(), matchb.matches.begin(), matchb.matches.end());
    //unmatched_tracks;
    res.unmatched_tracks.assign(
        matcha.unmatched_tracks.begin(), 
        matcha.unmatched_tracks.end());
    res.unmatched_tracks.insert(
        res.unmatched_tracks.end(),
        matchb.unmatched_tracks.begin(),
        matchb.unmatched_tracks.end());
    res.unmatched_detections.assign(
        matchb.unmatched_detections.begin(),
        matchb.unmatched_detections.end());
    printf("outracker::_match--  ... \n");
}

void tracker::_initiate_track(const DETECTION_ROW & detection)
{
    printf("intracker::_initiate_track---NOclsConf  ... \n");
    KAL_DATA data = kf->initiate(detection.to_xyah());
    KAL_MEAN mean = data.first;
    KAL_COVA covariance = data.second;

    this->tracks.push_back(Track(mean, covariance, this->_next_idx, this->n_init, 
                            this->max_age, detection.feature));
    _next_idx += 1;
    printf("outracker::_initiate_track---NOclsConf  ... \n");
}
void tracker::_initiate_track(const DETECTION_ROW& detection, CLSCONF clsConf)
{
    printf("intracker::_initiate_track---clsConf  ... \n");
    KAL_DATA data = kf->initiate(detection.to_xyah());
    KAL_MEAN mean = data.first;
    KAL_COVA covariance = data.second;

    this->tracks.push_back(Track(mean, covariance, this->_next_idx, this->n_init, 
                            this->max_age, detection.feature, clsConf.cls, clsConf.conf));
    _next_idx += 1;
    printf("outracker::_initiate_track---clsConf  ... \n");
}

DYNAMICM tracker::gated_matric(
    std::vector < Track > &tracks, 
    const DETECTIONS & dets,
    const std::vector < int >&track_indices,
    const std::vector < int >&detection_indices)
{
    printf("inDYNAMICM tracker::gated_matric  .232.. \n");
    FEATURESS features(detection_indices.size(), 256);
    int pos = 0;
  for (int i:detection_indices) {
        features.row(pos++) = dets[i].feature;
    }
    vector < int >targets;
  for (int i:track_indices) {
        targets.push_back(tracks[i].track_id);
    }
    DYNAMICM cost_matrix = this->metric->distance(features, targets);//kuang.feature and track.ID nn_mat.cpp
    DYNAMICM res = linear_assignment::getInstance()->gate_cost_matrix(
        this->kf, cost_matrix, tracks, dets, track_indices,
        detection_indices);
    printf("ouDYNAMICM tracker::gated_matric  ..246. \n");
    return res; //what?
    
}

DYNAMICM
tracker::iou_cost(
    std::vector < Track > &tracks,
    const DETECTIONS & dets,
    const std::vector < int >&track_indices,
    const std::vector < int >&detection_indices)
{
    //!!!python diff: track_indices && detection_indices will never be None.
    //    if(track_indices.empty() == true) {
    //        for(size_t i = 0; i < tracks.size(); i++) {
    //            track_indices.push_back(i);
    //        }
    //    }
    //    if(detection_indices.empty() == true) {
    //        for(size_t i = 0; i < dets.size(); i++) {
    //            detection_indices.push_back(i);
    //        }
    //    }
    printf("inDYNAMICM..tracker::iou_cost  ... \n");
    int rows = track_indices.size();
    int cols = detection_indices.size();
    DYNAMICM cost_matrix = Eigen::MatrixXf::Zero(rows, cols);
    for (int i = 0; i < rows; i++) {
        int track_idx = track_indices[i];
        if (tracks[track_idx].time_since_update > 1) {
            cost_matrix.row(i) = Eigen::RowVectorXf::Constant(cols, INFTY_COST);
            continue;
        }
        DETECTBOX bbox = tracks[track_idx].to_tlwh();
        int csize = detection_indices.size();
        DETECTBOXSS candidates(csize, 4);
        for (int k = 0; k < csize; k++) candidates.row(k) = dets[detection_indices[k]].tlwh;
        Eigen::RowVectorXf rowV = (1. - iou(bbox, candidates).array()).matrix().transpose();
        cost_matrix.row(i) = rowV;
    }
    printf("ouDYNAMICM..tracker::iou_cost  ... \n");
    return cost_matrix;
    
    
}

Eigen::VectorXf
    tracker::iou(DETECTBOX & bbox, DETECTBOXSS & candidates)
{
    printf("intracker::iou  ... \n");
    float bbox_tl_1 = bbox[0];
    float bbox_tl_2 = bbox[1];
    float bbox_br_1 = bbox[0] + bbox[2];
    float bbox_br_2 = bbox[1] + bbox[3];
    float area_bbox = bbox[2] * bbox[3];

    Eigen::Matrix < float, -1, 2 > candidates_tl;
    Eigen::Matrix < float, -1, 2 > candidates_br;
    candidates_tl = candidates.leftCols(2);
    candidates_br = candidates.rightCols(2) + candidates_tl;

    int size = int (candidates.rows());
    //    Eigen::VectorXf area_intersection(size);
    //    Eigen::VectorXf area_candidates(size);
    Eigen::VectorXf res(size);
    for (int i = 0; i < size; i++) {
        float tl_1 = std::max(bbox_tl_1, candidates_tl(i, 0));
        float tl_2 = std::max(bbox_tl_2, candidates_tl(i, 1));
        float br_1 = std::min(bbox_br_1, candidates_br(i, 0));
        float br_2 = std::min(bbox_br_2, candidates_br(i, 1));

        float w = br_1 - tl_1; w = (w < 0 ? 0 : w);
        float h = br_2 - tl_2; h = (h < 0 ? 0 : h);
        float area_intersection = w * h;
        float area_candidates = candidates(i, 2) * candidates(i, 3);
        res[i] = area_intersection / (area_bbox + area_candidates - area_intersection);
    }
    printf("outracker::iou  ... \n");
    return res;
    
}
