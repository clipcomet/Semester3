#include "opencv.h"
#include <iostream>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace cv;

int main()
{
    Opencv c;
    c.trackBar(); // add the trackbar
    VideoCapture cap = c.openVideo(0); // open video for cature
    while(true)
    {
        Mat OrgImg = c.capturevidio(cap); // create Mat from frame of carmara

        c.Both(OrgImg);  // run both ways og tracking
        //c.allColour(OrgImg); // run tracking based on HVS
        //c.allSubtrack(OrgImg); // run tracking base of Subtrackting background
        c.imShow(); // show in console

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break;
       }

    }

    return 0;
}
