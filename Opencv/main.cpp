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
int mode;

int main()
{
    Opencv c;
    c.trackBar(); // add the trackbar
    VideoCapture cap = c.openVideo(0); // open video for cature
    cout << "Chose mode"            << endl
         << "-------------------"   << endl
         << "1. Both"               << endl
         << "2.Colour Only"         << endl
         << "3.Subtracking Only"    << endl
         << "-------------------"   << endl
         << "Chosen mode?";
    cin >> mode;

    while(true)
    {
        Mat OrgImg = c.capturevidio(cap); // create Mat from frame of carmara
        switch(mode) {

        case 1 : c.Both(OrgImg);  // run both ways og tracking
            break;       // and exits the switch

        case 2 : c.allColour(OrgImg); // run tracking based on HVS
            break;

        case 3 : c.allSubtrack(OrgImg); // run tracking base of Subtrackting background
            break;

        default:
            cout << "Wrong choise";
            break;
        }



        c.imShow(); // show in console

        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break;
       }

    }

    return 0;
}
