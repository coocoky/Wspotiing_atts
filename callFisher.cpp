#include<stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"feature_option.h"
//#include"io.h"
#include"feat_desc.h"
extern "C" {
  #include <vl/generic.h>
#include<vl/imopv.h>
#include<vl/fisher.h>
}
#define MAGNIF 6
using namespace std;
using namespace cv;
//typedef struct {
//    int magnif =6;
//}dsiftparam;
denseSift *get_vl_dsift(float *data,int scale,int step,int imrow,int imcol)
{

     //image size;
    VlDsiftFilter *dsift ;
    VlDsiftDescriptorGeometry geom ;
    float *descriptor;
    VlDsiftKeypoint *frames;

    denseSift *featScale =new denseSift();
       printf("%d %d %d\n",imrow,imcol,scale);
       geom.binSizeX = scale ;
       geom.binSizeY = scale ;

       geom.numBinX = 4 ; //set to default
         geom.numBinY = 4 ;//set to default
         geom.numBinT = 8 ;//set to default
    dsift = vl_dsift_new (imrow,imcol) ;
    vl_dsift_set_geometry(dsift, &geom) ;
    vl_dsift_set_steps(dsift, step, step) ;
    featScale->numFrames = vl_dsift_get_keypoint_num (dsift) ;
        featScale->descrSize = vl_dsift_get_descriptor_size (dsift) ;
        descriptor =new float(featScale->descrSize*featScale->numFrames);
        //frames =new VlDsiftKeypoint(featScale->numFrames);
        vl_dsift_process (dsift, data) ;
        descriptor = (float*)vl_dsift_get_descriptors (dsift);
        frames = (VlDsiftKeypoint *)vl_dsift_get_keypoints (dsift) ;

            //featScale->descrs.reserve(featScale->descrSize*featScale->numFrames);
            //featScale->frames = vl_dsift_get_keypoints (dsift) ;
            //featScale->descrs.insert(featScale->descrs.end()+1,vl_dsift_get_descriptors (dsift), featScale->descrSize*featScale->numFrames);
            //featScale->descrs = vl_dsift_get_descriptors (dsift) ;
            printf("%d %d %d\n",featScale->numFrames,featScale->descrSize,scale);
            FILE *ftest = fopen("test.txt","w");
           int l=0;
            for(int j=0;j<featScale->numFrames;j++)
            {
                fprintf(ftest,"\n");
                fprintf(ftest,"%f %f",frames[j].x,frames[j].y);
               // for(int k=0;k<featScale->descrSize;k++)
                   // fprintf(ftest,"%f ",descriptor[l++]);
            }
            fclose(ftest);
            vl_dsift_delete (dsift) ;
            return featScale;


}



void get_vl_fisher_encode(Mat &encmat,denseSift feat,GMMTemp G,pcaTemp pca)
{
    //call factory function for vl_fisher_code
   int dim = 2*G.G * G.D;
    void *enc = vl_malloc(sizeof(float) * 2 * G.G * G.D);
    printf(" here %d %d %d\n",G.G,G.D,2 * G.G * G.D);

//    % Project into PCA space
//    if opts.useXY
//    xy = descrs(opts.SIFTDIM+1:end,:);
//    end
//    descrs=bsxfun(@minus, descrs(1:opts.SIFTDIM,:), PCA.mean);
//    descrs=PCA.eigvec'*descrs;
//    if opts.useXY
//    descrs = [descrs; xy];
//    end
   //Mat pcaMean,pcaVec;
    printf("row %d col %d\n pca rows %d pca cols%d",feat.descrs.rows,feat.descrs.cols,pca.mean.rows,pca.mean.cols);
    printf("\n eigVec %d %d",pca.eigvec.rows,pca.eigvec.cols);
    Mat descrs = Mat(feat.numFrames,feat.descrSize,CV_32FC1);
    for(int i=0;i<feat.numFrames;i++)
        descrs.row(i)=feat.descrs.row(i)-pca.mean;
    //Mat descrs = feat.descrs-pca.mean;
    descrs=pca.eigvec*feat.descrs.t();
     printf("\n eigVec %d %d %d",descrs.rows,descrs.cols,feat.numFrames);
     printf("changing to float vec");

     FILE *ftest =fopen("TestMu.txt","w");
     for(int iter =0;iter<G.G;iter++)
     {
         fprintf(ftest,"\n");
         for(int iter1=0;iter1<G.D;iter1++)
         {
             fprintf(ftest,"%f ",G.mu.at<float>(iter,iter1));
         }

     }
     fclose(ftest);
    // convert to float //
    float *mu = (float*)malloc(G.mu.rows*G.mu.cols*sizeof(float));

    float *Sigma = (float*)malloc(G.sigma.rows*G.sigma.cols*sizeof(float));
    float *We = (float*)malloc(G.we.rows*G.we.cols*sizeof(float));
    float *Descr = (float*)malloc(descrs.rows*descrs.cols*sizeof(float));
printf("changing to float vec");
    convert2Vec(G.mu,mu);
  printf("\nchanged to float vec");
    int k=0;
    FILE *ftest1 =fopen("TestMuAfter.txt","w");
    for(int iter =0;iter<G.G;iter++)
    {
        fprintf(ftest1,"\n");
        for(int iter1=0;iter1<G.D;iter1++)
        {
            //printf("%d\n",k);
            fprintf(ftest1,"%f ",G.sigmaraw[k++]);
        }

    }
    fclose(ftest1);
    printf("print complete");
    convert2Vec(descrs,Descr);
    k=0;
    FILE *ftest2 =fopen("ConvertedDesc.txt","w");
    for(int iter =0;iter<descrs.rows;iter++)
    {
        fprintf(ftest2,"\n");
        for(int iter1=0;iter1<descrs.cols;iter1++)
        {
            //printf("%d\n",k);
            fprintf(ftest2,"%f ",Descr[k++]);
        }

    }
    fclose(ftest2);
    printf("print complete");
    convert2Vec(G.sigma,Sigma);
    convert2Vec(G.we,We);
    printf("\nchanged to float vec");
// calling vl_feat library finction to encode */
    vl_fisher_encode
     (enc, VL_TYPE_FLOAT,
     mu, 64,192,
     Sigma,
     We,
     Descr, feat.numFrames,
     VL_FISHER_FLAG_IMPROVED
     ) ;
    printf("After encode");
    encmat =ConvertToMat(enc,dim,1,CV_32FC1);
   //printf("\nFV created %d %d",encodeFv.rows,encodeFv.cols);
//    FILE *fw = fopen("testFV.txt","w");
//    for (int i=0;i<dim;i++)
//        fprintf(fw,"%f\n",enc[i]);

//free(mu);
//free(Sigma);
//free(We);
    //free(Descr);
   // Mat encodeFv;
   printf("return");
    //return encodeFv;
}

void get_vl_phow(Mat &desc, Mat &frames, featParams param, float *grayIm, int imrow, int imcol)

{

        VlDsiftFilter *dsift ;
        VlDsiftDescriptorGeometry geom ;
       // Mat descr,frames;
        //denseSift phow_out ;

        //const int magnif =6;
        dsift = vl_dsift_new (imrow,imcol) ; // create a new dsift filter
        geom.numBinX = 4 ; //set to default geom
          geom.numBinY = 4 ;//set to default geom
          geom.numBinT = 8 ;//set to default geom
          vl_dsift_set_steps(dsift, param.step, param.step) ; //set the step size
          for (int i=0; i<param.numScale; i++)
              {
                  float sigma = param.scale[i] / MAGNIF ;
                  int off = floor(1 + 3/2 * (12 - param.scale[i])) ;
                 // printf("%d\n",param.scale[i]);
                  float* img_vec_smooth = (float*)malloc(imrow*imcol*sizeof(float)); //to store smoothed image in each scale
                  vl_imsmooth_f(img_vec_smooth,imcol,grayIm,imcol,imrow,imcol, sigma,sigma) ; // smoothing the  image

                  const float *descriptor; //temp descriptor for each scale
                  VlDsiftKeypoint *framescale; //temp frames for each scale
                  int numFrames,descrSize;
                  geom.binSizeX = param.scale[i] ;
                  geom.binSizeY = param.scale [i];
                  vl_dsift_set_geometry(dsift, &geom) ;
                              //vl_dsift_set_steps(dsift, step, step) ;
                  numFrames = vl_dsift_get_keypoint_num (dsift) ;
                  descrSize = vl_dsift_get_descriptor_size(dsift) ;
                  //printf("%d %d %d \n",numFrames,descrSize,phow_out.descrs.rows);
                  vl_dsift_process (dsift, img_vec_smooth) ;
                  descriptor = vl_dsift_get_descriptors (dsift);
                  framescale = (VlDsiftKeypoint *)vl_dsift_get_keypoints (dsift) ;
                  vl_dsift_set_bounds(dsift,
                                            VL_MAX(off, 0),
                                            VL_MAX(off, 0),
                                            imrow - 1,
                                            imcol - 1);

                  //l=0;
//                  FILE *ftest = fopen("testold.txt","w");
//                  for (int i = 0; i < numFrames; ++i)
//                  {
//                      fprintf(ftest,"\n");
//                    //for (int j = 0; j < ; ++j)
//                      fprintf(ftest,"%f %f %f %f ",framescale[i].x,framescale[i].y,framescale[i].s,framescale[i].norm);
//                  }

//                  FILE *fdes = fopen("descriptorinphow.txt","w");
//                  int ll=0;
//                  //FILE *ftest2 = fopen("testmatframe.txt","w");
//                                   for (int i = 0; i <numFrames; ++i)
//                                   {
//                                       fprintf(fdes,"\n");
//                                     for (int j = 0; j < descrSize; ++j)
//                                       fprintf(fdes,"%f ",descriptor[ll++]);

//                                   }
//                                   fclose(fdes);

//                  fclose(ftest);
                  double *tempScale =(double*)malloc(numFrames*4*sizeof(double));
                  int k=0;
                 // return;
//printf("check\n");
//FILE *ftest1 = fopen("testoldscale.txt","w");
                  for(int ii=0;ii<numFrames;ii++)
                  {
                     //printf("%d %d\n",(ii*4)+1,(ii+1)*4);
                      tempScale[k] =framescale[ii].x;
                      tempScale[k+1]=framescale[ii].y;
                     tempScale[k+2]=param.scale[i];
                      tempScale[k+3]=framescale[ii].norm;
                      //printf("%d %d %u %u\n",*tempScale,framescale[ii].x,tempScale,framescale);
                     // printf("%f %f %f \n",framescale[ii].x,tempScale[k],*(tempScale+k));
                      //tempScale[k]=framescale[ii].x;

                      //printf("%f",tempScale[k]);
            k=k+4;

                  }
                  //printf("check\n");
                 // printf("%f %f %f %f ",tempScale[0],tempScale[1],tempScale[2],tempScale[3]);
                 // FILE *ftest1 = fopen("testoldscale.txt","w");
//                  int l=0;
//                  for (int ii = 0; ii < numFrames; ++ii)
//                  {
//                      fprintf(ftest1,"\n");
//                    //for (int j = 0; j < ; ++j)
//                      fprintf(ftest1,"%f %f %f %f ",tempScale[l],tempScale[l+1],tempScale[l+2],tempScale[l+3]);
//                      l=l+4;
//                  }
//                   printf("check\n");

//                  fclose(ftest1);



                 // if (phow_out.descrs.empty()==true)
                  //{
                     // printf("here");
                      Mat dscale =Mat(numFrames,descrSize,CV_32FC1,(float*)descriptor);

                      Mat fscale = Mat(numFrames,4,CV_64FC1,tempScale);
                      desc.push_back(dscale);
                      frames.push_back(fscale);
                     // phow_out.descrs = ConvertToMat(descriptor,numFrames,descrSize,CV_32FC1); //Mat(numFrames,descrSize,CV_32FC1,descriptor);
                     // phow_out.frames = ConvertToMat(tempScale,numFrames,4,CV_64FC1);//Mat(numFrames,4,CV_64FC1,tempScale);
                     // phow_out.descrSize =descrSize;
                     // phow_out.numFrames =numFrames;
                      free(tempScale);
//                  }
//                  else
//                  {
//                     Mat dscale =ConvertToMat(descriptor,numFrames,descrSize,CV_32FC1);//Mat(numFrames,descrSize,CV_32FC1,descriptor);

//                     Mat fscale = ConvertToMat(tempScale,numFrames,4,CV_64FC1);//Mat(numFrames,4,CV_64FC1,tempScale);
//                      phow_out.descrs.push_back(dscale);
//                     //vconcat(phow_out.descrs,dscale,phow_out.descrs);
//                      dscale.release();
//                      phow_out.frames.push_back(fscale);
//                      //vconcat(phow_out.frames,fscale,phow_out.frames);
//                      phow_out.numFrames =phow_out.numFrames+numFrames;
//                      fscale.release();
//                      free(tempScale);

//                  }

                  //if()

                  FILE *ftest2 = fopen("testmatframe.txt","w");
                                   for (int i = 0; i <fscale.rows; ++i)
                                   {
                                       fprintf(ftest2,"\n");
                                     for (int j = 0; j < fscale.cols; ++j)
                                       fprintf(ftest2,"%f ",fscale.at<double>(i, j));
                                   }
                                   fclose(ftest2);
//printf("check\n");


//                  FILE *ftest2 = fopen("testmatframe.txt","w");
//                  for (int i = frames.rows-numFrames; i <frames.rows; ++i)
//                  {
//                      fprintf(ftest2,"\n");
//                    for (int j = 0; j < frames.cols; ++j)
//                      fprintf(ftest2,"%f ",frames.at<double>(i, j));
//                  }

//fclose(ftest2);


//A = Mat(1, 5, CV_32FC1, &data, 2);,
                  /* create a mat object of size numframes*descrsize */

                  free(img_vec_smooth);
                  //break;
          }
//          FILE *ftest2 = fopen("testmatframe.txt","w");
//                           for (int i = 0; i <phow_out.frames.rows; ++i)
//                           {
//                               fprintf(ftest2,"\n");
//                             for (int j = 0; j < phow_out.frames.cols; ++j)
//                               fprintf(ftest2,"%f ",phow_out.frames.at<double>(i, j));
//                           }
//                           fclose(ftest2);

//return phow_out;
}
//    printf("suman");
//    denseSift *t;
//    float* img_vec_smooth = (float*)malloc(imrow*imcol*sizeof(float)); //to store smoothed image in each scale
//    //FILE *ftest = fopen("test.txt","w");
//    const int magnif =6; //
//    VlDsiftFilter *dsift ;
//    VlDsiftDescriptorGeometry geom ;
//    dsift = vl_dsift_new (imrow,imcol) ; // create a new dsift filter
//    geom.numBinX = 4 ; //set to default geom
//      geom.numBinY = 4 ;//set to default geom
//      geom.numBinT = 8 ;//set to default geom
//      vl_dsift_set_steps(dsift, param.step, param.step) ; //set the step size

//    for (int i=1; i<param.numScale; i++)
//    {
//        float sigma = param.scale[i-1] / magnif ;
//            vl_imsmooth_f(img_vec_smooth,imcol,grayIm,imcol,imrow,imcol, sigma,sigma) ; // smoothing the  image

//            float *descriptor; //temp descriptor for each scale
//            VlDsiftKeypoint *frames; //temp frames for each scale
//            int numFrames,descrSize;

//            vl_dsift_set_geometry(dsift, &geom) ;
//            //vl_dsift_set_steps(dsift, step, step) ;
//            numFrames = vl_dsift_get_keypoint_num (dsift) ;
//            descrSize = vl_dsift_get_descriptor_size (dsift) ;
//               //descriptor =new float(featScale->descrSize*featScale->numFrames);
//                //frames =new VlDsiftKeypoint(featScale->numFrames);
//            vl_dsift_process (dsift, img_vec_smooth) ;
//            descriptor = (float*)vl_dsift_get_descriptors (dsift);
//            frames = (VlDsiftKeypoint *)vl_dsift_get_keypoints (dsift) ;
//            printf("%d %d",numFrames,descrSize);

//            FILE *ftest = fopen("test.txt","w");
//           int l=0;
//            for(int j=0;j<numFrames;j++)
//            {
//                fprintf(ftest,"\n");
//                fprintf(ftest,"%f %f\n",frames[j].x,frames[j].y);
//                for(int k=0;k<descrSize;k++)
//                    fprintf(ftest,"%f ",descriptor[l++]);
//            }
//            fclose(ftest);

//            /* copy to struct containing all scales*/
//    }
//    vl_dsift_delete(dsift);
//    return t;
//}
