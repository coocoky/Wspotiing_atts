#ifndef FEATURE_OPTION_H
#define FEATURE_OPTION_H

#endif // FEATURE_OPTION_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef struct{
     int  SIFTDIM ;//= 128;
     int useXY ;//= 0;
     int PCADIM ;//= 64;
     int numSpatialX;// = 6;
     int numSpatialY ;//= 2;
     int G ;//= 16;
     int scale[6];// ={2,4,6,8,10,12};
     int step ;//= 3;
     int numScale;// =6;
    int featDim;
} featParams;

typedef struct{
    char *modelPath;
    char *lexPath;
    char *pcaPath;// ="PCA.bin";
    char *gmmPath;// ="GMM.bin";
    char *attsPath;// ="atts.bin";
    char *ccaPath;//"CCA.bin"

}pathParam;


featParams set_feat_option();
