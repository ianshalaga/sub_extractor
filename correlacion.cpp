#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

float correlacion(const Mat &imagen1,const Mat &imagen2) {
	
	Mat imagen1_f,imagen2_f;
	imagen1.convertTo(imagen1_f,CV_32F);
	imagen2.convertTo(imagen2_f,CV_32F);
	
	Mat corr;
	matchTemplate(imagen1_f,imagen2_f,corr,TM_CCORR_NORMED);
	
	return corr.at<float>(0,0);  // corr solo tiene un pixel
}
