#ifndef IO_H
#define IO_H

#endif // IO_H

typedef struct{
float *eigvec;
float *mean;
int num;
int dim;
}pcaTemp;

typedef struct{
    int G;
    int D;
    float *we;
    float *mu;
    float *sigma;

}GMMTemp;

typedef struct{
    int K;
    float *Wx;
    float *wy;
    float *matts;
    float *mphocs;
}CCATemp;

pcaTemp readPCA(char*);

GMMTemp readGMM(char*);
CCATemp readCCA(char *);
float * readAttributeEmb(char *);
