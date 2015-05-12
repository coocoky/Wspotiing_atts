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

pcaTemp readPCA(char*);

GMMTemp readGMM(char*);
