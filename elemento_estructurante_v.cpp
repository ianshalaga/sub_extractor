#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

Mat elemento_estructurante_v() {
	
	Mat ee(3,3,CV_8UC(1),Scalar(255));
	
//	Fila 0
	ee.at<uchar>(0,0) = 0;
	ee.at<uchar>(0,1) = 255;
	ee.at<uchar>(0,2) = 0;
	
//	Fila 1
	ee.at<uchar>(1,0) = 0;
	ee.at<uchar>(1,1) = 255;
	ee.at<uchar>(1,2) = 0;
	
//	Fila 2
	ee.at<uchar>(2,0) = 0;
	ee.at<uchar>(2,1) = 255;
	ee.at<uchar>(2,2) = 0;
	
	return ee;
}
