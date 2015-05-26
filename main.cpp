//#include "mainwindow.h"
//#include <QApplication>
#include <iostream>
#include<stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"feature_option.h"
//#include"io.h"
#include"feat_desc.h"
extern "C" {
  #include <vl/generic.h>
#include<vl/dsift.h>
}

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    VL_PRINT ("Hello world!") ;
    if( argc != 2)
        {
         cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
         return -1;
        }
      VL_PRINT ("Hello world!") ;
     cout << "start";
        Mat image,grayIm;
        image = imread("w3_4.jpg");   // Read the file
        cout << "image loaded";

        if(! image.data )         // Check for invalid input
        {
            cout <<  "Could not open or find the image" << std::endl ;
            return -1;
        }
        cvtColor(image, grayIm, cv::COLOR_BGR2GRAY);


        int k=0;
        float *grayImg=(float*)malloc(grayIm.rows*grayIm.cols*sizeof(float));
        for (int i = 0; i < grayIm.rows; ++i)
          for (int j = 0; j < grayIm.cols; ++j)
            grayImg[k++]= grayIm.at<unsigned char>(i, j);

//        FILE *ftest;
//                ftest = fopen("test2.txt","w");
//                //uchar *data =grayIm.data;
//       k=0;
//        for (int i = 0; i < grayIm.rows; ++i)
//        {
//            fprintf(ftest,"\n");
//          for (int j = 0; j < grayIm.cols; ++j)
//          {
//              int bin =grayImg[k++]>127;
//              fprintf(ftest,"%d", bin);
//          }
//        }
//fclose(ftest);

        featParams param =featParams();
        pathParam resPath;


        //int featDim;
        //prepare_opts(param,resPath);
        printf("aqui");

//        /* calling dsift function of vl_feat library*/

        denseSift feat = get_vl_phow(param,grayImg,grayIm.rows,grayIm.cols);
        printf(" In main %d %d\n",feat.descrs.rows,feat.descrs.cols);

//normalize sift is due

        resPath.lexPath ="lexicon.bin";
        resPath.pcaPath ="PCA.bin";
        resPath.gmmPath ="GMM.bin";
        resPath.attsPath ="attModels.bin";
        resPath.ccaPath="CCA.bin";
        /* reading PCA file from matlab*/
        pcaTemp PCAModel = readPCA(resPath.pcaPath);
        FILE *ftest1;
        ftest1 = fopen("testPCAMain.txt","w");
       // GM1M->we = ConvertToMat(GMM->refWe,1,GMM->G);
      for (int iter=0;iter<PCAModel.dim;iter++)
        fprintf(ftest1,"%f \n",PCAModel.mean.at<float>(0,iter));
        fclose(ftest1);

       // printf("PCA attributes \n%d %d\n",PCAModel.dim,PCAModel.num);

        /* reading GMM file from Matlab*/
        //GMMTemp *GMM =new GMMTemp();
        GMMTemp GMM =readGMM(resPath.gmmPath);
        printf("\nGMM attributes %d %d\n",GMM.D,GMM.G);
        // printf("%u\n",GMM.we.data);
        FILE *ftest;
        ftest = fopen("testGMMMain.txt","w");
        //GMM->we = ConvertToMat(GMM->refWe,1,GMM->G);
      for (int iter=0;iter<GMM.G;iter++)
        fprintf(ftest,"%f \n",GMM.we.at<float>(0,iter));
        //fclose(ftest);

        for(int iter =0;iter<GMM.G;iter++)
        {
            fprintf(ftest,"\n");
            for(int iter1=0;iter1<GMM.D;iter1++)
            {
                fprintf(ftest,"%f ",GMM.mu.at<float>(iter,iter1));
            }

        }

        fclose(ftest);


        /* calling vl_fisher function of vl_feat library to encode the SIFT vectors */
        Mat FV = get_vl_fisher_encode(feat,GMM,PCAModel);
        FILE *ftest2 = fopen("testFV.txt","w");
        for (int iter=0;iter<FV.rows;iter++)
          fprintf(ftest2,"%f \n",FV.at<float>(0,iter));
        fclose(ftest);
        //printf("%d %d\n",FV.rows,FV.cols);
       // Mat FV = Mat::zeros(1,param.featDim,DataType<float>::type);
//        FV.data = fv;

//         read embedding matrix and CCA matrix */

       Mat  W =readAttributeEmb(resPath.attsPath);
        //Mat embW = Mat::zeros(param.featDim,param.numAtts,DataType<float>::type);
        //embW.data =W;
       printf("\n%d %d\n",W.rows,W.cols);

        CCATemp CCA = readCCA(resPath.ccaPath);
        //Mat CCA = Mat::zeros(param.featDim,param.numAtts,DataType<float>::type);

        //CCA.data = cca;

        W =W.colRange(0,FV.rows);
        printf("\nFV dim %d %d\n W dim %d %d\nCCA dim %d %d",FV.rows,FV.cols,W.rows,W.cols,CCA.Wx.rows,CCA.Wx.cols);
//        /* multiply fv,embedding matrix,cca matrix like atts = (fv*W')*CCA' */
        Mat atts =W*FV;// FV* CCA.Wx;
        atts =CCA.Wx.t() *atts;
//        /* take l2 norm */

//        /* read a lexicon file precomputed */
//        float *lex = readLexicon(resPath.lexPath);

//        /* take a dot product in matlab lex*atts'*/

//        Mat S = atts.t() * lex;

        /* sort and get the result */










        // Create a window for display.
        //namedWindow( "Display window" );

//        // Show our image inside it.
      // imshow( "Display window", grayIm );

       // waitKey(0);              // Wait for a keystroke in the window
        return 0;
}


//int main (int argc, const char * argv[]) {
//  VL_PRINT ("Hello world!") ;
//  return 0;
//}
