#ifndef FEATURE_OPTION_H
#define FEATURE_OPTION_H

#endif // FEATURE_OPTION_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

typedef struct featParams{
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
    featParams()
    {SIFTDIM = 128;
        useXY = 0;
        PCADIM = 64;
        numSpatialX = 6;
        numSpatialY = 2;
        G = 16;
       // param.scale ;//{2,4,6,8,10,12};
        for (int i=1;i<6;i++)
            scale[i-1]=2*i;
        step = 3;
        numScale =6;
        featDim = 2*(PCADIM+2)*numSpatialX*numSpatialY*G;
    }
} featParams;

typedef struct pathParam{
    const char *modelPath;
    const char *lexPath;
    const char *pcaPath;// ="PCA.bin";
    const char *gmmPath;// ="GMM.bin";
    const char *attsPath;// ="atts.bin";
    const char *ccaPath;//"CCA.bin"
    pathParam()
    {
        lexPath ="lexicon.bin";
        pcaPath ="PCA.bin";
        gmmPath ="GMM.bin";
        attsPath ="attModels.bin";
        ccaPath="CCA.bin";
    }

}pathParam;


featParams set_feat_option();
