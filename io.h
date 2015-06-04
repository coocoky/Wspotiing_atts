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

typedef struct CCATemp{
    int K;
    Mat Wx;
    Mat Wy;
    Mat matts;
    Mat mphocs;
    float *mattsraw;
    float *mphocsraw;
    float *Wxraw;
    float *Wyraw;
    const char *ccaFname;
    CCATemp(){}
    CCATemp(const char *fname)
    {
      int row; //temp
        ccaFname=fname;
        FILE *fid = fopen(fname, "rb");
        fread(&row, sizeof(int),1 ,fid);

        fread(&K, sizeof(int),1 ,fid);
        Wxraw =(float*)malloc(sizeof(float)*row*K);

        fread(Wxraw, sizeof(float), row*K,fid);

        Wx =Mat(row,K,CV_32FC1,Wxraw);
        Wyraw =(float*)malloc(sizeof(float)*row*K);

        fread(Wyraw, sizeof(float), row*K,fid);

        Wy =Mat(row,K,CV_32FC1,Wyraw);

        mattsraw = (float*) malloc(sizeof(float)*row*1);
        fread(mattsraw, sizeof(float), row*1,fid);
        matts = Mat(row,1,CV_32FC1,mattsraw);
        //free(buffer);
        mphocsraw = (float*) malloc(sizeof(float)*row*1);
        fread(mphocsraw, sizeof(float), row*1,fid);
        mphocs = Mat(row,1,CV_32FC1,mphocsraw);


    }
}CCATemp;

pcaTemp readPCA(const char*);

GMMTemp readGMM(const char*);
CCATemp readCCA(const char *);
void readAttributeEmb(float *,const char *);
void readAttributeEmbDim(int &N,int &D,const char *fname);
Mat ConvertToMat(void*vec, int row, int col,int type);
void convert2Vec(Mat data,float *vec);
//void readPhocLex(Mat &lexMat,const char *);
//void readPhocLexDim(int &N,int &D,const char *fname);
void readMatData(float *,const char *);
void readMatDim(int &N,int &D,const char *fname);
