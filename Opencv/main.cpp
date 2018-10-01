#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;



vector<vector<Point> > contours; // vektor points for outline of object
vector<vector<Point> >canny;
// HSV color range
//--------------------------------
int iLowH = 0;
int iHighH = 179;

int iLowS = 0;
int iHighS = 255;

int iLowV = 0;
int iHighV = 84;
//----------------------------
int kernel_size = 3;

int countup = 0;
int countloop = 10; //used to slow down updates on less imported things (loops)

Mat imgThresholded;
Mat imgHSV;

 int main( int argc, char** argv )
 {

    VideoCapture cap(0); //capture the video from web cam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }
//---------------------------Control----------------------------------------------------------
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"



  //Create trackbars in "Control" window
 cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
 cvCreateTrackbar("HighH", "Control", &iHighH, 179);

  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 cvCreateTrackbar("HighS", "Control", &iHighS, 255);

  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
 cvCreateTrackbar("HighV", "Control", &iHighV, 255);

///////////////////////////////////////////////////////////////////////////////////////////////

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }



  cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from RGB to HSV



   inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

  //(remove small objects from the foreground "or trying to :P)
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

   //(fill small holes in the foreground again trying to :P)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );



//------------ Vetor outline-------------------------
  findContours(imgThresholded,contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
  drawContours(imgOriginal,contours,-1,(255,255,0),3);




  //----------Test draw eage-----------------------
  Mat edge, draw;
  //cvtColor(img, gray, CV_BGR2GRAY);

  Canny( imgThresholded, edge, 0, 150, kernel_size);
imgOriginal.copyTo( draw, edge);
  imshow("edge", edge);
  imshow("draw", draw);
////////////////////////////////////////////////


//-------------find center--------------------

  Moments mu = moments(imgThresholded, true);
  Point center;
  center.x = mu.m10 / mu.m00;
  center.y = mu.m01 / mu.m00;
  circle(imgOriginal, center, 4, Scalar(255,0,255));




/////////////////////////////////////////////

  //-----------print cords--------------

  string x = to_string(center.x);
  string y = to_string(center.y);
  string text = "x= " + x + " y= "+ y;
  putText(imgOriginal,text,center,1,1,Scalar(255,0,0),2);

  ///////////////////////////////////////////////



  //-------------------------show------------------------
  imshow("Thresholded Image", imgThresholded); //show the thresholded image
//  blur( imgThresholded,imgThresholded,Size( 3, 3 ));                                        // blur
  imshow("smoothed Image", imgThresholded); //show the thresholded image
  imshow("Original", imgOriginal); //show the original image

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break;
       }

   //------------- less freqent update---------
    if (countup <= countloop)
    {
      cout << center.x << " " << center.y << " " << endl;
      countup = 0;
    }
    else
    {
        countup++;
    }
    ////////////////////////////////////////////////


    }

   return 0;

}
