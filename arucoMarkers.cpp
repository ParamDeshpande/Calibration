#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/aruco.hpp"

#include <cctype>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define framesPerSecond 25e0
#define chessBoardSquareW 9
#define chessBoardSquareL 7

using namespace std;
using namespace cv;


// To extract 2d Corners from the image 
const float calibrationSquareDimension = 0.01905f; //Meters 
const float arucoSquareDimension = 0.1016f; //Meters 
const cv::Size chessboardDimensions = Size(chessBoardSquareW,chessBoardSquareL);

void createKnownBoardPosition(Size boardSize, float squareEdgeLength, vector<Point3f>& corners){
    for(int i = 0 ; i <boardSize.height ; i++){
        for(int j = 0; j < boardSize.width ; j++){
            /* To store all the locations of corners*/
            corners.push_back(Point3f(j * squareEdgeLength , i * squareEdgeLength , 0.0f));
        }
    }
}

void getChessboardCorners(vector<Mat> images, vector<vector<Point2f>>& allFoundCorners, bool showResults = false){
    for(vector<Mat>::iterator iter = images.begin(); iter != images.end(); iter++){
        /*To hold all the points in the image a Buffer*/
        vector<Point2f> pointBuf;
        /*Returns a bool object if it gound or not the corners  */
        /* Imp look for adaptive thresholding/normalize the image CV_CALIB_FASTCHECK */
        bool found = findChessboardCorners(*iter , Size(chessBoardSquareW,chessBoardSquareL), pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        if(found == true){
            allFoundCorners.push_back(pointBuf);
        }
        /* Defined as an ip parameter for the function */
        if(showResults == true){
            drawChessboardCorners(*iter,Size(chessBoardSquareW,chessBoardSquareL), pointBuf, found );
            imshow("Looking for Corners", *iter);
            waitKey(0);
        }
    }
}

void createArukoMarkers(){
    /* To insert the image in the marker */
    cv::Mat outputMarker;
    /* have selected 4 by 4 for fastest detection*/
    Ptr<aruco::Dictionary> MarkerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
    for(int i = 0 ; i< 50 ; i++){
        aruco::drawMarker(MarkerDictionary, i, 500, outputMarker ,1 );
        ostringstream convert;
        string imageName = "4x4Marker_";
        convert <<  imageName << i << ".jpg";
        imwrite(convert.str(), outputMarker);
    }
}

int main(int argv, char **argc){
//    createArukoMarkers();
    cv::Mat frame;
    cv::Mat drawToFrame;
    cv::Mat cameraMatrix = Mat::eye(3,3,CV_64F);
    cv::Mat distanceCoefficients;
    
    /* For those lucky images who get selected. */
    std::vector<cv::Mat> savedImages;
    std::vector<std::vector<cv::Point2f>> markerCorners, rejectedCandidates;

    VideoCapture vid(0);
    if(!vid.isOpened()){
        return 0;
    }

    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

    while(true){
        if(!vid.read(frame))
            break;

        std::vector<Vec2f> foundPoints; 
        bool found = false;
        /* In the above code there were a set no of images here we are doing it live 
        * same series of steps 
        * as above has
        */
        found = findChessboardCorners(frame, chessboardDimensions, foundPoints,CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        /*To overlay the found cornes */
        frame.copyTo(drawToFrame);
        drawChessboardCorners(drawToFrame, chessboardDimensions, foundPoints, found);
        if(found)
            imshow("Webcam", drawToFrame);
        else 
            imshow("Webcam", frame);
            char character = waitKey(1000 / framesPerSecond);

    }
    return 0;

}