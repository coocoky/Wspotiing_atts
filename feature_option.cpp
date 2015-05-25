#include"feature_option.h"

void SetParams()
{
    featParams param;
    param.SIFTDIM = 128;
    param.useXY = 0;
    param.PCADIM = 64;
    param.numSpatialX = 6;
    param.numSpatialY = 2;
    param.G = 16;
   // param.scale ;//{2,4,6,8,10,12};
    for (int i=1;i<6;i++)
        param.scale[i-1]=2*i;
    param.step = 3;
    param.numScale =6;
    param.featDim = 2*(param.PCADIM+2)*param.numSpatialX*param.numSpatialY*param.G;
}
