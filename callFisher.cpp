#include<stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"feature_option.h"
#include"io.h"
#include"feat_desc.h"
extern "C" {
  #include <vl/generic.h>
#include<vl/imopv.h>
#include<vl/fisher.h>
}
using namespace std;
using namespace cv;
typedef struct {
    int magnif =6;
}dsiftparam;
denseSift get_vl_dsift(float *data,int scale,int step,int imrow,int imcol)
{

     //image size;
    VlDsiftFilter *dsift ;
    VlDsiftDescriptorGeometry geom ;

    denseSift featScale;
       printf("%d %d %d\n",imrow,imcol,scale);
       geom.binSizeX = scale ;
       geom.binSizeY = scale ;

       geom.numBinX = 4 ; //set to default
         geom.numBinY = 4 ;//set to default
         geom.numBinT = 8 ;//set to default
    dsift = vl_dsift_new (imrow,imcol) ;
    vl_dsift_set_geometry(dsift, &geom) ;
    vl_dsift_set_steps(dsift, step, step) ;
    featScale.numFrames = vl_dsift_get_keypoint_num (dsift) ;
        featScale.descrSize = vl_dsift_get_descriptor_size (dsift) ;
        vl_dsift_process (dsift, data) ;

            featScale.frames = vl_dsift_get_keypoints (dsift) ;
            featScale.descrs = vl_dsift_get_descriptors (dsift) ;
            printf("%d %d\n",featScale.numFrames,featScale.descrSize);
            vl_dsift_delete (dsift) ;
            return featScale;


}

denseSift  get_vl_phow(featParams param, vector<float> grayIm, int imrow, int imcol)
{
    denseSift featGray,featGrayAll;
    dsiftparam dsiftopts;
    int start,end,l;

    //test image

//    for(int j=0;j<imrow;j++)
//    {
//        fprintf(ftest,"\n");
//        for(int k=0;k<imcol;k++)
//            fprintf(ftest,"%f ",grayIm);
//    }

    float* img_vec_smooth = (float*)malloc(imrow*imcol*sizeof(float));
    FILE *ftest = fopen("test.txt","w");

    for (int i=1; i<param.numScale; i++)
    {
        float sigma = param.scale[i-1] / dsiftopts.magnif ;
            vl_imsmooth_f(img_vec_smooth,imcol,grayIm.data(),imcol,imrow,imcol, sigma,sigma) ; //can't figure out how to call this in C

            /* call vl_dsift here */

            featGray=get_vl_dsift(img_vec_smooth,param.scale[i-1],param.step,imrow,imcol);
            fprintf(ftest,"scale %d\n",i);
            for(int j=0;j<featGray.numFrames;j++)
            {
                fprintf(ftest,"\n");
                for(int k=0;k<featGray.descrSize;k++)
                    fprintf(ftest,"%f ",featGray.descrs);
            }


            //start = featGrayAll.numFrames+1;
            //end = start+featGray.numFrames-1;
            //l=0;
            /*for (int k=start;k<end;k++)
            {
                featGrayAll.descrs[k] =featGray.descrs[l];
                featGrayAll.frames[k] = featGray.frames[l];

                l++;
            }*/
            //featGrayAll.numFrames=featGrayAll.numFrames+featGray.numFrames;
            //featGrayAll.descrSize = featGray.descrSize;

    }
    fclose(ftest);



return featGrayAll;



        }

float *get_vl_fisher_encode(denseSift feat,GMMTemp G,pcaTemp pca)
{
    //call factory function for vl_fisher_code
   int dim = 2*G.G * G.D;
    float *enc = (float*)vl_malloc(sizeof(float) * 2 * G.G * G.D);
    printf("%d",2 * G.G * G.D);

//    % Project into PCA space
//    if opts.useXY
//    xy = descrs(opts.SIFTDIM+1:end,:);
//    end
//    descrs=bsxfun(@minus, descrs(1:opts.SIFTDIM,:), PCA.mean);
//    descrs=PCA.eigvec'*descrs;
//    if opts.useXY
//    descrs = [descrs; xy];
//    end
   Mat pcaMean,pcaVec;


    vl_fisher_encode
     (enc, VL_TYPE_FLOAT,
     G.mu, G.D, G.G,
     G.sigma,
     G.we,
     feat.descrs, feat.numFrames,
     VL_FISHER_FLAG_IMPROVED
     ) ;
    FILE *fw = fopen("test.txt","w");
    for (int i=0;i<dim;i++)
        fprintf(fw,"%f\n",enc[i]);


    return enc;
}
