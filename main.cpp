//#include "mainwindow.h"
//#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<feature_option.h>
#include<feat_desc.h>
extern "C" {
  #include <vl/generic.h>
#include<vl/dsift.h>
}

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
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

        featParams *param;
        pathParam *resPath;
        prepare_opts(param,resPath);

        /* calling dsift function of vl_feat library*/

        denseSift feat = get_vl_phow(param,grayIm);



        /* reading PCA file from matlab*/
        //PCA = readPCA(resPath);

        /* reading GMM file from Matlab*/
        //GMM = readGMM(resPath);

        /* calling vl_fisher function of vl_feat library to encode the  */
        //float const *fv = get_fisher_encode(feat,GMM,PCA);

        /* read embedding matrix and CCA matrix */

        /* multiply fv,embedding matrix,cca matrix */

        /* read a lexicon file precomputed */

        /* take a dot product */










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
