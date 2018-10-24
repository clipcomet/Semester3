#ifndef OPENCV_H
#define OPENCV_H
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


class Opencv
{
public:
    Opencv();

    cv::Mat capturevidio(cv::VideoCapture);
    cv::Mat convertRGBHSV(cv::Mat);
    cv::Mat Thresholded(cv::Mat);
    cv::Mat erodedilate(cv::Mat);
    cv::Point findCenter(cv::Mat);
    cv::Mat printcenter (cv::Mat,cv::Point);
    cv::Mat printtextcenter (cv::Mat,cv::Point);
    cv::Mat vectoroutline (cv::Mat,cv::Mat);
    void imShow (cv::Mat,std::string);
    cv::Point allInOne (cv::Mat);
    void trackBar();
    cv::VideoCapture openVideo(int device);

private:

    int iLowH = 0;
    int iHighH = 179;

    int iLowS = 0;
    int iHighS = 255;

    int iLowV = 0;
    int iHighV = 84;


};



#endif // OPENCV_H
