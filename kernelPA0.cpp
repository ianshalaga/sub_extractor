#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

Mat kernelPA0() {
	
	Mat kernel(3,3,CV_64F,Scalar(-1));
	
	kernel.at<double>(1,1) = 10; // centro
	
	kernel.at<double>(0,1) = -2; // centro superior
	kernel.at<double>(2,1) = -2; // centro inferior
	
	return kernel;
}
