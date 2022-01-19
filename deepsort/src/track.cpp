#include "track.h"
#include <iostream>

Track::Track(KAL_MEAN & mean, KAL_COVA & covariance, int track_id, int n_init, int max_age, const FEATURE & feature)
{
    printf("inTrack::Track---NO .cls.conf ... \n");
    this->mean = mean;
    this->covariance = covariance;
    this->track_id = track_id;
    this->hits = 1;
    this->age = 1;
    this->time_since_update = 0;
    this->state = TrackState::Tentative;
    features = FEATURESS(1, 256);
    features.row(0) = feature;  //features.rows() must = 0;

    this->_n_init = n_init;
    this->_max_age = max_age;
    printf("ouTrack::Track---NO .cls.conf ... \n");
}

Track::Track(KAL_MEAN & mean, KAL_COVA & covariance, int track_id, int n_init, int max_age, const FEATURE & feature, int cls, float conf)
{
    printf("inTrack::Track---yep .cls.conf ... \n");
    this->mean = mean;
    this->covariance = covariance;
    this->track_id = track_id;
    this->hits = 1;
    this->age = 1;
    this->time_since_update = 0;
    this->state = TrackState::Tentative;
    features = FEATURESS(1, 256);
    features.row(0) = feature;  //features.rows() must = 0;

    this->_n_init = n_init;
    this->_max_age = max_age;

    this->cls = cls;
    this->conf = conf;
    printf("ouTrack::Track---yep .cls.conf ... \n");
}

void Track::predit(KkalmanFilter * kf)
{
    /*Propagate the state distribution to the current time step using a
       Kalman filter prediction step.

       Parameters
       ----------
       kf : kalman_filter.KalmanFilterd
       The Kalman filter.
     */

    printf("inTrack::predit ... \n");
    kf->predict(this->mean, this->covariance);


    this->age += 1;
    this->time_since_update += 1;
    printf("ouTrack::predit ... \n");
}

void Track::update(KkalmanFilter * const kf, const DETECTION_ROW & detection)
{
    printf("inTrack::update ...NO.clsconf \n");
    KAL_DATA pa = kf->update(this->mean, this->covariance, detection.to_xyah());
    this->mean = pa.first;
    this->covariance = pa.second;

    featuresAppendOne(detection.feature);
    //    this->features.row(features.rows()) = detection.feature;
    this->hits += 1;
    this->time_since_update = 0;
    if (this->state == TrackState::Tentative && this->hits >= this->_n_init) {
        this->state = TrackState::Confirmed;
    }
    printf("ouTrack::update ...NO.clsconf \n");
}

void Track::update(KkalmanFilter * const kf, const DETECTION_ROW & detection, CLSCONF pair_det)
{
    printf("inTrack::update ...yep.clsconf \n");
    KAL_DATA pa = kf->update(this->mean, this->covariance, detection.to_xyah());
    this->mean = pa.first;
    this->covariance = pa.second;

    featuresAppendOne(detection.feature);
    //    this->features.row(features.rows()) = detection.feature;
    this->hits += 1;
    this->time_since_update = 0;
    if (this->state == TrackState::Tentative && this->hits >= this->_n_init) {
        this->state = TrackState::Confirmed;
    }
    this->cls = pair_det.cls;
    this->conf = pair_det.conf;
    printf("ouTrack::update ...yep.clsconf \n");
}

void Track::mark_missed()
{
	printf("inTrack::mark_missed.... \n");
    if (this->state == TrackState::Tentative) {
        this->state = TrackState::Deleted;
    } else if (this->time_since_update > this->_max_age) {
        this->state = TrackState::Deleted;
    }
    printf("ouTrack::mark_missed.... \n");
}

bool Track::is_confirmed()
{
    return this->state == TrackState::Confirmed;
}

bool Track::is_deleted()
{
    return this->state == TrackState::Deleted;
}

bool Track::is_tentative()
{
    return this->state == TrackState::Tentative;
}

DETECTBOX Track::to_tlwh()
{
    printf("inTrack::to_tlwh.... \n");
    DETECTBOX ret = mean.leftCols(4);
    ret(2) *= ret(3);
    ret.leftCols(2) -= (ret.rightCols(2) / 2);
    printf("ouTrack::to_tlwh.... \n");
    return ret;
    
}

void Track::featuresAppendOne(const FEATURE & f)
{
    printf("inTrack::featuresAppendOne.... \n");
    int size = this->features.rows();
    FEATURESS newfeatures = FEATURESS(size + 1, 256);
    newfeatures.block(0, 0, size, 256) = this->features;
    newfeatures.row(size) = f;
    features = newfeatures;
    printf("ouTrack::featuresAppendOne.... \n");
}
