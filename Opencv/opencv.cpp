#include "opencv.h"
#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <stdio.h>
#include <stdlib.h>
using namespace cv;
using namespace std;

Opencv::Opencv()
{
    iLowH = 0;
    iHighH = 179;

    iLowS = 42;
    iHighS = 255;

    iLowV = 0;
    iHighV = 255;

    lowThreshold = 0;
    max_lowThreshold = 100;
    scale = 39;

}

Mat Opencv::capturevidio(VideoCapture cap)
{
        Mat imgOriginal;
        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             //break;
        }

         return imgOriginal;

}

VideoCapture Opencv::openVideo (int device)
{
    VideoCapture cap(device); //capture the video from web cam

        if ( !cap.isOpened() )  // if not success, exit program
        {
             cout << "Cannot open the web cam" << endl;
             return -1;
        }

        return cap;
}

void Opencv::trackBar ()
{
    int i = rand() % 100;
    std::string x = std::to_string(i);
    const char* Control = x.c_str();
    namedWindow(Control, CV_WINDOW_AUTOSIZE); //create a window called "Control"



    //Create trackbars in "Control" window
    cvCreateTrackbar("LowH", Control, &iLowH, 179); //Hue (0 - 179)
    cvCreateTrackbar("HighH", Control, &iHighH, 179);

    cvCreateTrackbar("LowS", Control, &iLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", Control, &iHighS, 255);

    cvCreateTrackbar("LowV", Control, &iLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", Control, &iHighV, 255);
    cvCreateTrackbar( "Min Threshold:", Control, &lowThreshold, 100);
    cvCreateTrackbar("scale", Control, &scale, 179);
}

void Opencv::imShow () // img to show and name of Window its showen in
{

    for (int i = 0; i < Matvector.size(); i++)
    {
        string x = Matvectorname[i];
        namedWindow(x);
        resizeWindow(x, 400,400);
        imshow(x,Matvector[i]);

    }
    Matvector.clear();
    Matvectorname.clear();
}

Mat Opencv::convertRGBHSV(Mat imgOriginal) // outputs imgHSV
{
    Mat imgHSV;
    cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from RGB to HSV
    if (devMode == 2)
    {
        Matvector.push_back (imgHSV);
        Matvectorname.push_back("HVS");
    }
    return imgHSV;

}

Mat Opencv::Thresholded(Mat imgHSV) // sliders and return a Threshold img
{
    Mat imgThresholded;

    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    if (devMode == 2 or devMode == 1)
    {
        Matvector.push_back (imgThresholded);
        Matvectorname.push_back("Threshold");
    }
    return imgThresholded;

}

Mat Opencv::Blur(Mat ThrashImg,int x)
{
    Mat BlurImg;
    blur(ThrashImg,BlurImg,Size(x,x));
    if (devMode == 2)
    {
        Matvector.push_back (BlurImg);
        Matvectorname.push_back("BlurImg");
    }
    return BlurImg;
}

Mat Opencv::ImgCanny(Mat BlurImg,Mat org)
{
    Mat dst,detected_edges;
    /// Canny detector
    Canny( BlurImg, detected_edges,0,100,3);
    if (devMode == 2 or devMode == 1 )
    {
        Matvector.push_back (detected_edges);
        Matvectorname.push_back("Edges");
    }

    return detected_edges;
}

Point Opencv::findCenter(Mat imgThresholded) //find Center of Threshold img
{
    Moments mu = moments(imgThresholded, true);
    Point center;
    center.x = mu.m10 / mu.m00;
    center.y = mu.m01 / mu.m00;

    return center;
}

Mat Opencv::printcenter (Mat imgOriginal,Point center,const char* name) // adds circle to center
{
    Mat temp = imgOriginal.clone();
    circle(temp, center, 10, Scalar(255,0,255));
    cout << center.x << " " << center.y << " " << endl;

    std::string x = std::to_string(center.x);
    std::string y = std::to_string(center.y);
    //string x = this->IntToString(center.x);
    //string y = this->IntToString(center.y);
    string text = "x= " + x + " y= "+ y;
    putText(temp,text,center,1,1,Scalar(255,0,0),2);
    if (devMode == 2 or devMode == 1)
    {
        Matvector.push_back (temp);
        Matvectorname.push_back(name);
    }
    return temp;


}

void Opencv::allColour(Mat &OrgImg)
{

    Opencv o;
    //Mat OrgImg = o.capturevidio(cap);

    Mat HvsImg = Opencv::convertRGBHSV(OrgImg);

    Mat ThrashImg = Opencv::Thresholded(HvsImg);

    Mat BlurImg = Opencv::Blur(ThrashImg,5);

    Mat CanImg = Opencv::ImgCanny(BlurImg,OrgImg);

    Point center = Opencv::findCenter(ThrashImg);

    Mat final = Opencv::printcenter(OrgImg,center,"Point colour");

    Mat imgErode = Opencv::erodeImg(ThrashImg);

    Mat imgDilate = Opencv::dilateImg(ThrashImg);

    o.imShow();

}

void Opencv::allSubtrack(Mat &OrgImg2)
{
    Mat SubedImg,GrayImg,mask,FinalImg;

    if(First == true)
    {
        string temp;
        cout << "Ready for Static pic" << endl <<  "Insert Dev mode level" << endl << "----------------------" << endl << "0. NonDev" << endl << "1. Simple output" << endl << "2. All output" << endl << "----------------------" << endl << "Devmode? ";
        cin >> devMode;
        StaticImg = OrgImg2;
        First = false;
    }
    else
    {

        absdiff(OrgImg2,StaticImg, SubedImg); //subtrack one img from another
        cvtColor(SubedImg, GrayImg, CV_BGR2GRAY); //Grayscale the picture

        mask = GrayImg>scale; // create a mask that includes all pixel that changed their value more then "scale"

        OrgImg2.copyTo(FinalImg,mask); // adds the mask to the streamed img and creates a new one
        Point subCenter = Opencv::findCenter(mask);

        FinalImg = OrgImg2.clone(); // clone the orgImg for the center placement
        Opencv::printcenter(FinalImg,subCenter,"Point Sub ");

        if (devMode == 2)
        {
            Matvector.push_back (StaticImg);
            Matvector.push_back (OrgImg2);
            Matvector.push_back (mask);
            Matvector.push_back (FinalImg);
            Matvectorname.push_back("StaticImg");
            Matvectorname.push_back("OrgImg2");
            Matvectorname.push_back("Mask");
            Matvectorname.push_back("FinalImg");

        }

        if (devMode == 1)
        {
            Matvector.push_back (StaticImg);
            Matvector.push_back (FinalImg);
            Matvector.push_back (mask);
            Matvectorname.push_back("StaticImg");
            Matvectorname.push_back("FinalImg");
            Matvectorname.push_back("Mask");
        }

    }
}

void Opencv::Both (Mat &OrgImg)
{
   Mat OrgImg2 = OrgImg.clone();


   Mat SubedImg,GrayImg,mask,FinalImg;

   if(First == true)
   {
       string temp;
       cout << "Ready for Static pic" << endl <<  "Insert Dev mode level" << endl << "----------------------" << endl << "0. NonDev" << endl << "1. Simple output" << endl << "2. All output" << endl << "----------------------" << endl << "Devmode? ";
       cin >> devMode;
       StaticImg = OrgImg2;
       First = false;
   }
   else
   {

       absdiff(OrgImg2,StaticImg, SubedImg); //subtrack one img from another
       cvtColor(SubedImg, GrayImg, CV_BGR2GRAY); //Grayscale the picture

       mask = GrayImg>scale; // create a mask that includes all pixel that changed their value more then "scale"

       OrgImg2.copyTo(FinalImg,mask); // adds the mask to the streamed img and creates a new one
       Point subCenter = Opencv::findCenter(mask);

       FinalImg = OrgImg2.clone(); // clone the orgImg for the center placement
       Opencv::printcenter(FinalImg,subCenter,"Point sub");

       if (devMode == 2)
       {
           Matvector.push_back (StaticImg);
           Matvector.push_back (OrgImg2);
           Matvector.push_back (mask);
           Matvector.push_back (FinalImg);
           Matvectorname.push_back("StaticImg");
           Matvectorname.push_back("OrgImg2");
           Matvectorname.push_back("Mask");
           Matvectorname.push_back("FinalImg");

       }

       if (devMode == 1)
       {
           Matvector.push_back (StaticImg);
           Matvector.push_back (FinalImg);
           Matvector.push_back (mask);
           Matvectorname.push_back("StaticImg");
           Matvectorname.push_back("FinalImg");
           Matvectorname.push_back("Mask");
       }



    Mat HvsImg = Opencv::convertRGBHSV(OrgImg);

    Mat ThrashImg = Opencv::Thresholded(HvsImg);

    Mat BlurImg = Opencv::Blur(ThrashImg,5);

    Mat CanImg = Opencv::ImgCanny(BlurImg,OrgImg);

    center = Opencv::findCenter(ThrashImg);

    Mat final = Opencv::printcenter(OrgImg,center,"Point colour");

    Mat imgErode = Opencv::erodeImg(ThrashImg);

    Mat imgDilate = Opencv::dilateImg(ThrashImg);



    }
}
Mat Opencv::erodeImg(Mat ThrashImg)
{
    Mat imgErode;
    erode(ThrashImg, imgErode, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    if (devMode == 2)
    {
        Matvector.push_back (imgErode);
        Matvectorname.push_back("Erode");
    }
    return imgErode;
}

Mat Opencv::dilateImg(Mat ThrashImg)
{
    Mat imgDilate;
    erode(ThrashImg, imgDilate, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)) );
    if (devMode == 2)
    {
        Matvector.push_back (imgDilate);
        Matvectorname.push_back("Dilate");
    }
    return imgDilate;
}

void Opencv::SetFinal(bool Fin)
{
    First = Fin;
}
