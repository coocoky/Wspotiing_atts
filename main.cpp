//#include "mainwindow.h"
//#include <QApplication>
#include <iostream>
#include<stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include"feature_option.h"
#include"feat_desc.h"
#include"io.h"
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



        vector<float> grayImg;
        for (int i = 0; i < grayIm.rows; ++i)
          for (int j = 0; j < grayIm.cols; ++j)
            grayImg.push_back(grayIm.at<unsigned char>(i, j));


        featParams param;
        pathParam resPath;
        param.featDim = 2*(param.PCADIM+2)*param.numSpatialX*param.numSpatialY*param.G;
        //prepare_opts(param,resPath);
        printf("aqui");

//        /* calling dsift function of vl_feat library*/

        denseSift feat = get_vl_phow(param,grayImg,grayIm.rows,grayIm.cols);

//normalize sift is due

        resPath.lexPath ="lexicon.bin";
        resPath.pcaPath ="PCA.bin";
        resPath.gmmPath ="GMM.bin";
        resPath.attsPath ="atts.bin";
        resPath.ccaPath="CCA.bin"
        /* reading PCA file from matlab*/
        pcaTemp PCAModel = readPCA(resPath.pcaPath);

        printf("PCA attributes \n%d %d",PCAModel.dim,PCAModel.num);

        /* reading GMM file from Matlab*/
        GMMTemp GMM = readGMM(resPath.gmmPath);

        /* calling vl_fisher function of vl_feat library to encode the SIFT vectors */
        float const *fv = get_fisher_encode(feat,GMM,PCAModel);
        Mat FV = Mat::zeros(1,param.featDim,DataType<float>::type);
        FV.data = fv;

        /* read embedding matrix and CCA matrix */

       float  *W =readAttributeEmb(resPath.attspath);
        Mat embW = Mat::zeros(param.featDim,param.numAtts,DataType<float>::type);
        embW.data =W;

        float *cca = readCCA(resPath.ccaPath);
        Mat CCA = Mat::zeros(param.featDim,param.numAtts,DataType<float>::type);

        CCA.data = cca;


        /* multiply fv,embedding matrix,cca matrix like atts = (fv*W')*CCA' */
        Mat atts = (FV * W) * CCA;
        /* take l2 norm */

        /* read a lexicon file precomputed */
        lex = readLexicon(resPath.lexPath);

        /* take a dot product in matlab lex*atts'*/

        Mat S = atts * lex;

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
