#include "nn_matching.h"
#include <iostream>

using namespace Eigen;

NearNeighborDisMetric::NearNeighborDisMetric(
    NearNeighborDisMetric::METRIC_TYPE metric, 
    float matching_threshold, int budget)
{
	printf("inNearNeighborDisMetric::NearNeighborDisMetric... \n");
    if (metric == euclidean) {
		printf("111111... \n");
        _metric =
            &NearNeighborDisMetric::_nneuclidean_distance;
    } else if (metric == cosine) {
		printf("2222222... \n");
        _metric =
            &NearNeighborDisMetric::_nncosine_distance;
    }

    this->mating_threshold = matching_threshold;
    this->budget = budget;
    std::cout << "this->samples [" << std::endl;
    for (auto i : this->samples)
       std::cout << i.first << ", ";
       //std::cout << i.second << ", ";
    std::cout << "]" <<std::endl;
    //std::cout  << "21----this->samples.frist:" << this->samples.begin<< "this->samples.second " << this->samples.end<<std::endl;
    this->samples.clear();   
    printf("ouNearNeighborDisMetric::NearNeighborDisMetric... \n");
}

DYNAMICM 
NearNeighborDisMetric::distance(
    const FEATURESS & features,
    const std::vector < int >&targets)
{//kuang .feature  and  track.ID
	printf("inDYNAMICM..NearNeighborDisMetric::distance... \n");
    DYNAMICM cost_matrix = Eigen::MatrixXf::Zero(targets.size(), features.rows());
    int idx = 0;
  for (int target:targets) {
        cost_matrix.row(idx) = (this->*_metric) (this->samples[target], features);
        idx++;                 //hanshu  ming  13hang,, track.?*256      det.?*256  return  Eigen::VectorXf
    }
    printf("ouDYNAMICM..NearNeighborDisMetric::distance... \n");
    return cost_matrix;
    
}

void
 NearNeighborDisMetric::partial_fit(
     std::vector <TRACKER_DATA > &tid_feats,
    std::vector < int >&active_targets)
{
	printf("inDYNAMICM..NearNeighborDisMetric:::partial_fit... \n");
    /*python code:
     * let feature(target_id) append to samples;
     * && delete not comfirmed target_id from samples.
     * update samples;
     */
  for (TRACKER_DATA & data:tid_feats) {
        int track_id = data.first;
        FEATURESS newFeatOne = data.second;
        std::cout << "samples [" << std::endl;
        for (auto i : samples)
           std::cout << i.first << ", ";
           //std::cout << i.second << ", ";
        std::cout << "]" << std::endl;
        //std::cout  << "69---samples:" << samples.find(track_id)<<"------"<<samples.end()<< "danwei.. " << std::endl;
        if (samples.find(track_id) != samples.end()) {  //append
            int oldSize = samples[track_id].rows();
            int addSize = newFeatOne.rows();
            int newSize = oldSize + addSize;

            if (newSize <= this->budget) {
			    printf("74 \n");
                FEATURESS newSampleFeatures(newSize, 256);
                newSampleFeatures.block(0, 0, oldSize, 256) = samples[track_id];
                newSampleFeatures.block(oldSize, 0, addSize, 256) = newFeatOne;
                samples[track_id] = newSampleFeatures;
            } else {
                if (oldSize < this->budget) {   //original space is not enough;
					printf("81\n");

                    FEATURESS newSampleFeatures(this->budget, 256);
                    if (addSize >= this->budget) {
						printf("85\n");

                        newSampleFeatures = newFeatOne.block(0, 0, this->budget, 256);
                    } else {
                        newSampleFeatures.block(0, 0, this->budget - addSize, 256) =
                            samples[track_id].block(addSize - 1, 0, this->budget - addSize, 256).eval();
                        newSampleFeatures.block(this->budget - addSize, 0, addSize,256) = newFeatOne;
                    }
                    samples[track_id] = newSampleFeatures;
                } else {        //original space is ok;
					printf("95\n");
                    if (addSize >= this->budget) {
						printf("97\n");
                        samples[track_id] = newFeatOne.block(0, 0, this->budget, 256);
                    } else {
						printf("100n");
                        samples[track_id].block(0, 0, this->budget - addSize, 256) =
                            samples[track_id].block(addSize - 1, 0, this->budget - addSize, 256).eval();
                        samples[track_id].block(this->budget - addSize, 0, addSize, 256) = newFeatOne;
                    }
                }
            }
        } else {                //not exit, create new one;
            samples[track_id] = newFeatOne;
        }
    }                           //add features;

    //erase the samples which not in active_targets;
    for (std::map < int, FEATURESS >::iterator i = samples.begin(); i != samples.end();) {
        bool flag = false;
      for (int j:active_targets) if (j == i->first) { flag = true; break; }
        if (flag == false)samples.erase(i++);
        else i++;
    }
    printf("ouDYNAMICM..NearNeighborDisMetric:::partial_fit... \n");
}

Eigen::VectorXf
    NearNeighborDisMetric::_nncosine_distance(
        const FEATURESS & x, const FEATURESS & y)
{
	printf("inEigen::VectorXf...NearNeighborDisMetric::_nncosine_distance... \n");
    MatrixXf distances = _cosine_distance(x, y);
    VectorXf res = distances.colwise().minCoeff().transpose();
    printf("ouEigen::VectorXf...NearNeighborDisMetric::_nncosine_distance... \n");
    return res;
    
}

Eigen::VectorXf
    NearNeighborDisMetric::_nneuclidean_distance(
        const FEATURESS & x, const FEATURESS & y)
{
	printf("inEigen::VectorXf...NearNeighborDisMetric::_nneuclidean_distance... \n");
    MatrixXf distances = _pdist(x, y);
    VectorXf res = distances.colwise().maxCoeff().transpose();
    res = res.array().max(VectorXf::Zero(res.rows()).array());
    printf("ouEigen::VectorXf...NearNeighborDisMetric::_nneuclidean_distance... \n");
    return res;
    
}

Eigen::MatrixXf
    NearNeighborDisMetric::_pdist(const FEATURESS & x, const FEATURESS & y)
{
	printf("inEigen::MatrixXf...NearNeighborDisMetric::_pdist... \n");
    int len1 = x.rows(), len2 = y.rows();
    if (len1 == 0 || len2 == 0) {
        return Eigen::MatrixXf::Zero(len1, len2);
    }
    MatrixXf res = -2.0 * x * y.transpose();
    res = res.colwise() + x.rowwise().squaredNorm();
    res = res.rowwise() + y.rowwise().squaredNorm().transpose();
    res = res.array().max(MatrixXf::Zero(res.rows(), res.cols()).array());
    printf("ouEigen::MatrixXf...NearNeighborDisMetric::_pdist... \n");
    return res;
    
}

Eigen::MatrixXf
    NearNeighborDisMetric::_cosine_distance(
        const FEATURESS & a, const FEATURESS & b, bool data_is_normalized)
{
	printf("inEigen::MatrixXf...NearNeighborDisMetric::_cosine_distance... \n");
    FEATURESS aa = a;
    FEATURESS bb = b;
    if (!data_is_normalized) {
        //undo:
        for (int i = 0; i < a.rows(); ++i) {
            aa.row(i) =  a.row(i) / sqrt(a.row(i).squaredNorm());
        }
        for (int i = 0; i < b.rows(); ++i) {
            bb.row(i) =  b.row(i) / sqrt(b.row(i).squaredNorm());
        }        
    }
    MatrixXf res = 1. - (aa * bb.transpose()).array();
    printf("ouEigen::MatrixXf...NearNeighborDisMetric::_cosine_distance... \n");
    return res;
    
}
