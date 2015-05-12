#ifndef FEATURE_OPTION_H
#define FEATURE_OPTION_H

#endif // FEATURE_OPTION_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef struct{
    const int  SIFTDIM = 128;
    const int useXY = 0;
    const int PCADIM = 64;
    const int numSpatialX = 6;
    const int numSpatialY = 2;
    const int G = 16;
    const int scale[6] ={2,4,6,8,10,12};
    const int step = 3;
    const int numScale =6;
    int featDim;
} featParams;

typedef struct{
    char *modelPath;
    char *lexPath;
    char *lexPath;
    char *pcaPath;// ="PCA.bin";
    char *gmmPath;// ="GMM.bin";
    char *attsPath;// ="atts.bin";
    char *ccaPath;//"CCA.bin"

}pathParam;


