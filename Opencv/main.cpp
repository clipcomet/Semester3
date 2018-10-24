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





 int main( int argc, char** argv )
 {
    Opencv o;

    VideoCapture cap = o.openVideo(0);
    o.trackBar();


    while (true)
        {

            Mat orgimg = o.capturevidio(cap);
            /*
            Mat HVSimg = o.convertRGBHSV(orgimg);

            Mat thrashold = o.Thresholded(HVSimg);

            Mat cleanThrashold = o.erodedilate(thrashold);

            Mat vectorrr = o.vectoroutline(cleanThrashold,orgimg);



            o.imShow(orgimg,"ORG");
            o.imShow(HVSimg,"hvsing");
            o.imShow(thrashold,"thrashhold");
            o.imShow(cleanThrashold,"cleanThrashold");
            o.imShow(vectorrr,"vectorr");
            o.imShow(centerimg,"centerimg");
            */

            Point ur5 = o.allInOne(orgimg);





            if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
           {
                cout << "esc key is pressed by user" << endl;
                break;
           }
        }




   return 0;

     }

