#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <stdint.h>

const int fps = 25;

int main(int argv, char** argc){
    cv::Mat frame;
    cv::VideoCapture vid(0);

    if(!vid.isOpened()){
        return -1;
    }
    while (vid.read(frame))
    {
        imshow("webcam", frame);
        if(cvWaitKey(1000/fps) >= 0)
        break;

    }
    return 1;

}