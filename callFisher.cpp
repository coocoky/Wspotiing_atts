#include<stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<feature_option.h>
#include<feat_desc.h>
extern "C" {
  #include <vl/generic.h>
}
using namespace std;
using namespace cv;
typedef struct {
    int magnif =6;
}dsiftparam;
denseSift get_vl_dsift(uchar *data,int scale,int step)
{
    int M,N; //image size;
    VlDsiftFilter *dsift ;
    denseSift featScale;
        /* note that the image received from MATLAB is transposed */
    dsift = vl_dsift_new (M, N) ;
    vl_dsift_set_steps(dsift, step, step) ;
    featScale.numFrames = vl_dsift_get_keypoint_num (dsift) ;
        featScale.descrSize = vl_dsift_get_descriptor_size (dsift) ;
        vl_dsift_process (dsift, data) ;

            featScale.frames = vl_dsift_get_keypoints (dsift) ;
            featScale.descrs = vl_dsift_get_descriptors (dsift) ;

            return featScale;


}

denseSift  get_vl_phow(featParams *param, Mat grayIm)
{
    denseSift featGray[param->numScale];
    dsiftparam dsiftopts;
    for (int i=1; i<param->numScale; i++)
    {
        float sigma = param->scale[i] / dsiftopts.magnif ;
           // ims = vl_imsmooth(grayIm.data, sigma) ; can't figure out how to call this in C

            /* call vl_dsift here */

            featGray[i-1]=get_vl_dsift(grayIm.data,param->scale[i-1],param->step);



    }





        }


