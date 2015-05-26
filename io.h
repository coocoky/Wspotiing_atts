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

typedef struct GMMTemp{
    int G;
    int D;
    Mat we;
    Mat mu;
    Mat sigma;

//    GMMTemp()
//    {
//    }

//    GMMTemp(int nGaussian, int Dim)
//    {
//        G =nGaussian;
//        D =Dim;
//        //we = Mat(G,D)

//    }

//    GMMTemp(const GMMTemp &temp)
//    {
//        G =temp.G;
//        D =temp.D;
//        we=temp.we.clone();
//        mu =temp.mu.clone();
//        sigma =temp.sigma.clone();
//    }

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
void convert2Vec(Mat data,float *vec );
