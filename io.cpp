#include"io.h"
#include<stdio.h>
#include<malloc.h>

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
    PCA.eigvec = buffer;
    free(buffer);
    buffer = (float*)malloc(sizeof(float)*PCA.dim);
   result = fread(buffer, sizeof(float), PCA.dim,fid);
    PCA.mean = buffer;//fread(fid, [D,1], '*single');
    free(buffer);
    fclose(fid);
    return PCA;
}

GMMTemp readGMM(char *fname)
{
    GMMTemp GMM;
    int a;
    FILE *fid = fopen(fname, "r");
    fread(&a, sizeof(int),1 ,fid);
    GMM.G =a;
    fread(&a, sizeof(int),1 ,fid);
    GMM.D =a;
    float *buffer = (float*)malloc(sizeof(float)*GMM.G);
    int success = fread(buffer, sizeof(float), GMM.G,fid);
    GMM.we = buffer;
     buffer = (float*)malloc(sizeof(float)*GMM.G*GMM.D);
    sucess = fread(buffer, sizeof(float), GMM.G*GMM.D,fid);
    GMM.mu = buffer;
    buffer = (float*)malloc(sizeof(float)*GMM.G*GMM.D);
    sucess = fread(buffer, sizeof(float), GMM.G*GMM.D,fid);

    GMM.sigma = buffer;


    fclose(fid);

    return GMM;

}
