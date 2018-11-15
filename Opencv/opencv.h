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
    cv::Mat capturevidio(cv::VideoCapture cap);
    cv::VideoCapture openVideo(int device);
    void trackBar();
    void imShow();
    cv::Mat convertRGBHSV(cv::Mat imgOriginal);
    cv::Mat Thresholded(cv::Mat imgHSV);

    cv::Mat Blur(cv::Mat ThrashImg, int x);
    cv::Mat ImgCanny(cv::Mat BlurImg,cv::Mat Org);
    cv::Mat Can2Img(cv::Mat org, cv::Mat Can);
    cv::Point findCenter(cv::Mat imgThresholded);
    cv::Mat printcenter(cv::Mat imgOriginal, cv::Point center);
    void allColour(cv::Mat &imgOrg);
    cv::Mat erodeImg(cv::Mat ThrashImg);
    cv::Mat dilateImg(cv::Mat ThrashImg);
    void allSubtrack(cv::Mat &OrgImg);
    void Both(cv::Mat &OrgImg);
    void SetFinal(bool Fin);

private:

    int iLowH ;
    int iHighH;

    int iLowS;
    int iHighS;

    int iLowV;
    int iHighV;

    int lowThreshold = 0;
    int max_lowThreshold = 100;
    int scale;
    bool First = true;
    cv::Mat StaticImg;
    int devMode= 2; // 0 == off 1 == Only final pic 2 == all windows

    std::vector<cv::Mat> Matvector{};
    std::vector<const char*> Matvectorname{};
    cv::Point subCenter;
    cv::Point center;



};

#endif // OPENCV_H
