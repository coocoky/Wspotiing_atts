#ifndef IO_H
#define IO_H

#endif // IO_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
typedef struct{
Mat eigvec;
Mat mean;
int num;
int dim;
}pcaTemp;

typedef struct{
    int G;
    int D;
    Mat we;
    Mat mu;
    Mat sigma;

}GMMTemp;

typedef struct{
    int K;
    Mat Wx;
    Mat wy;
    Mat matts;
    Mat mphocs;
}CCATemp;

pcaTemp readPCA(char*);

GMMTemp readGMM(char*);
CCATemp readCCA(char *);
Mat readAttributeEmb(char *);
Mat ConvertToMat(float*vec, int row, int col);
