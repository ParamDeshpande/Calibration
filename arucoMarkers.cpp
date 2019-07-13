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
#include <fstream>      // std::ofstream

#define framesPerSecond 25e0
#define chessBoardSquareW 9
#define chessBoardSquareL 7
#define minimumImages 2
using namespace std;
using namespace cv;

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
    createArukoMarkers();
    return 0;

}
