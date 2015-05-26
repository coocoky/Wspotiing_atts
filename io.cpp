#include"io.h"
#include<stdio.h>
#include<malloc.h>

Mat ConvertToMat(float *vec,int row, int col)
{
     Mat retmat = Mat(row,col,CV_32FC1);
    // FILE *ft = fopen("testGMM.txt","w");
//     for (int iter=0;iter<col;iter++)
//       fprintf(ft,"%f %f\n ",retmat.at<float>(0,iter),vec[iter]);
//     fclose(ft);
     //free(buffer);
         //printf("%d %d\n",row,col);
         //printf("%u %f\n",vec,vec[0]);
     int k=0;
     for (int i = 0; i < row; ++i)
         for(int j=0;j<col;j++)
     {
         //printf("%f",vec[i]);

          //for (int j = 0; j < data.cols; ++j)
            //buffer[k++]= data.at<float>(i, j);
         retmat.at<float>(i,j)=vec[k++];
     }
     return retmat;
}
float *convert2Vec(Mat data )
{
   float *buffer = (float*)malloc(sizeof(float)*data.rows*data.cols);
    int k=0;
   for (int i = 0; i < data.rows; ++i)
     for (int j = 0; j < data.cols; ++j)
       buffer[k++]= data.at<float>(i, j);
   return buffer;
}

pcaTemp readPCA(char *fname)
{
    pcaTemp PCA;
    int a;
    FILE *fid = fopen(fname, "r");
    fread(&a, sizeof(int),1 ,fid);
    PCA.num = a;
    fread(&a, sizeof(int),1 ,fid);
    PCA.dim = a;
    /*PCA.dim=fread(fid, 1,'*int32');
    /* allocate space for eigvec and mean*/
    float *buffer = (float*)malloc(sizeof(float)*PCA.num*PCA.dim);


    int result = fread(buffer, sizeof(float), PCA.num*PCA.dim,fid);
    PCA.eigvec=ConvertToMat(buffer,PCA.num,PCA.dim);
    //PCA.eigvec = buffer;
    free(buffer);
    buffer = (float*)malloc(sizeof(float)*PCA.dim);
   result = fread(buffer, sizeof(float), PCA.dim,fid);
    PCA.mean = ConvertToMat(buffer,1,PCA.dim);//fread(fid, [D,1], '*single');
    free(buffer);
    FILE *ftest;
    ftest = fopen("testPCA.txt","w");
   // GMM->we = ConvertToMat(GMM->refWe,1,GMM->G);
  for (int iter=0;iter<PCA.dim;iter++)
    fprintf(ftest,"%f \n",PCA.mean.at<float>(0,iter));
    fclose(ftest);
    //fclose(fid);
    return PCA;
}

GMMTemp readGMM(char *fname)
{
    GMMTemp GMM;
    int G,Dim;
    FILE *fid = fopen(fname, "r");
    fread(&G, sizeof(int),1 ,fid);
    GMM.G =G;
    //printf("\n inside  read GMM%d\n",a);
    fread(&Dim, sizeof(int),1 ,fid);
    GMM.D =Dim;
    //GMMTemp GMM = GMMTemp(G,D);
    //printf("Inside Read GMM %d\n",a);
    float *buffer = (float*)malloc(sizeof(float)*GMM.G);
    int success = fread(buffer, sizeof(float), GMM.G,fid);
    GMM.we = ConvertToMat(buffer,1,GMM.G);

    printf("%u %f\n",buffer,buffer[0]);
    printf("%u\n",GMM.we.data);
//    FILE *ft = fopen("testGMM.txt","w");
//    for (int iter=0;iter<GMM.G;iter++)
//      fprintf(ft,"%f %f\n ",buffer[iter],GMM.we.at<float>(0,iter));//,buffer[iter]);
//    fclose(ft);
    free(buffer);
     buffer = (float*)malloc(sizeof(float)*GMM.G*GMM.D);
    success = fread(buffer, sizeof(float), GMM.G*GMM.D,fid);
    GMM.mu = ConvertToMat(buffer,GMM.G,GMM.D);

    free(buffer);
    buffer = (float*)malloc(sizeof(float)*GMM.G*GMM.D);
    success = fread(buffer, sizeof(float), GMM.G*GMM.D,fid);

    GMM.sigma = ConvertToMat(buffer,GMM.G,GMM.D);

    free(buffer);
    FILE *ft = fopen("testGMM.txt","w");
        for (int iter=0;iter<GMM.G;iter++)
          fprintf(ft,"%f \n ",GMM.we.at<float>(0,iter));//,buffer[iter]);

        for(int iter =0;iter<GMM.G;iter++)
        {
            fprintf(ft,"\n");
            for(int iter1=0;iter1<GMM.D;iter1++)
            {
                fprintf(ft,"%f ",GMM.mu.at<float>(iter,iter1));
            }

        }
        fclose(ft);

//    fclose(fid);

    return GMM;

}

Mat readAttributeEmb(char *fname)
{
    float *emb;
    int N,D;
    FILE *fid = fopen(fname, "r");
    fread(&N, sizeof(int),1 ,fid);

    fread(&D, sizeof(int),1 ,fid);


    emb = (float*)malloc(sizeof(float)*N*D);

     fread(emb, sizeof(float), N*D,fid);
     //Mat embMat =Mat(N,D,CV_32FC1,emb);
     Mat embMat =ConvertToMat(emb,N,D);
     free(emb);
    return embMat;
}

 CCATemp readCCA(char *fname)
{
    CCATemp CCA;
    float *buffer ;
    int N,D;
    FILE *fid = fopen(fname, "r");
    fread(&N, sizeof(int),1 ,fid);

    fread(&D, sizeof(int),1 ,fid);

    buffer =(float*)malloc(sizeof(float)*N*D);

    fread(buffer, sizeof(float), N*D,fid);

    CCA.Wx =ConvertToMat(buffer,N,D);
    free(buffer);
    buffer =(float*)malloc(sizeof(float)*N*D);
    fread(buffer, sizeof(float), N*D,fid);
    CCA.wy =ConvertToMat(buffer,N,D);
    free(buffer);
    buffer = (float*) malloc(sizeof(float)*N*1);
    fread(buffer, sizeof(float), N*1,fid);
    CCA.matts = ConvertToMat(buffer,N,1);
    free(buffer);
    buffer = (float*) malloc(sizeof(float)*N*1);
    fread(buffer, sizeof(float), N*1,fid);
    CCA.mphocs = ConvertToMat(buffer,N,1);
    free(buffer);
    CCA.K =D;
    return CCA;


}

