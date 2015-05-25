#ifndef FEAT_DESC_H
#define FEAT_DESC_H

#endif // FEAT_DESC_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"io.h"
extern "C" {
  #include <vl/generic.h>
#include <vl/dsift.h>
}
using namespace std;
using namespace cv;

typedef struct
{
    int numFrames ;
    int descrSize ;
    //std::vector <VlDsiftKeypoint> frames ;
    //std::vector<float> descrs;
    Mat descrs;
    Mat frames;
}denseSift;

denseSift get_vl_phow(featParams, float*, int , int);
denseSift *get_vl__dsift(float **data,int scale,int step);
Mat get_vl_fisher_encode(denseSift,GMMTemp,pcaTemp);
