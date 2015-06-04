#ifndef IO_H
#define IO_H
#include<fstream>
#include<iostream>

#endif // IO_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;
typedef struct pcaTemp{
Mat eigvec;
Mat mean;
int num;
int dim;
const char*pcaFileName;
float *eigvecraw;
float *meanraw;
pcaTemp()
{
}

pcaTemp(const char *fName)
{
    pcaFileName=fName;
    // read the dimension

    FILE *fid = fopen(pcaFileName, "rb");

    int a,status;

    fread(&a, sizeof(int),1 ,fid);

    num = a;


    fread(&a, sizeof(int),1 ,fid);
    dim = a;
    /*PCA.dim=fread(fid, 1,'*int32');
    /* allocate space for eigvec and mean*/
    eigvecraw = (float*)malloc(sizeof(float)*num*dim);
     status = fread(eigvecraw, sizeof(float), num*dim,fid);
     if (status==0)
         printf("Error reading eigvec from PCA.bin, %d",status);
    //eigvecraw = new float[num*dim];

   // meanraw = new float[num*dim];
    //pcaFile.read((char*)meanraw,sizeof(float)*num*dim);
    meanraw = (float*)malloc(sizeof(float)*dim);
    status = fread(meanraw, sizeof(float), dim,fid);
    if (status==0)
        printf("Error reading means from PCA.bin");

    /* convert to mat*/

  eigvec = Mat(num,dim,CV_32FC1,eigvecraw);
  mean = Mat(1,dim,CV_32FC1,meanraw);
}
}pcaTemp;

typedef struct GMMTemp{
    int G;
    int D;
    Mat we;
    Mat mu;
    Mat sigma;
    float *weraw;
    float *muraw;
    float *sigmaraw;
    const char *GMMFileName;

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
    GMMTemp()
    {
    }

    GMMTemp(const char *fName)
    {
        GMMFileName=fName;
        // read the dimension

        FILE *fid = fopen(GMMFileName, "rb");

        int a,status;

        fread(&a, sizeof(int),1 ,fid);

        G = a;


        fread(&a, sizeof(int),1 ,fid);
        D = a;

        weraw = (float*)malloc(sizeof(float)*G);
        status = fread(weraw, sizeof(float), G,fid);
        we = Mat(1,G,CV_32FC1,weraw);


         muraw = (float*)malloc(sizeof(float)*G*D);
        status = fread(muraw, sizeof(float), G*D,fid);
        mu = Mat(G,D,CV_32FC1,muraw);


        sigmaraw = (float*)malloc(sizeof(float)*G*D);
        status = fread(sigmaraw, sizeof(float), G*D,fid);
        sigma = Mat(G,D,CV_32FC1,sigmaraw);

    }

}GMMTemp;

typedef struct{
    int K;
    Mat Wx;
    Mat wy;
    Mat matts;
    Mat mphocs;
}CCATemp;

pcaTemp readPCA(const char*);

GMMTemp readGMM(const char*);
CCATemp readCCA(const char *);
Mat readAttributeEmb(const char *);
Mat ConvertToMat(void*vec, int row, int col,int type);
void convert2Vec(Mat data,float *vec);
