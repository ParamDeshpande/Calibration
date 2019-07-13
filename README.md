# Camera Calibration

calculation of distortion coefficients, aruco markers for AR , webcam access (low level for development)

### Prerequisites

cpp 11/14 
opencv 3.4

### Installing

general cpp code execution
on command line use

```
 g++ camera_calib.cpp `pkg-config --cflags --libs opencv`
```

## References 
* [opencv docs](https://docs.opencv.org/2.4/doc/tutorials/calib3d/camera_calibration/camera_calibration.html) An overview of camcalib working
* [Zhangs method](https://www.researchgate.net/publication/303233579_Zhang's_Camera_Calibration_Algorithm_In-Depth_Tutorial_and_Implementation) In depth explaination and owner Zhangs method for camera calibration using chessboard and assymetric circles.
* [Youtube OpenCV Basics](https://www.youtube.com/watch?v=l_4fNNyk1aw&list=PLAp0ZhYvW6XbEveYeefGSuLhaPlFML9gP) The above code has been extracted from here.


