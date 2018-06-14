#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

Mat or_mascaras(const vector<Mat> &mascaras) {
	
	int filas = mascaras[0].rows;
	int columnas = mascaras[0].cols;
	
	Mat mask(filas,columnas,CV_8UC(1),Scalar(0));
	
	for(int k=0;k<mascaras.size();k++) { 
		bitwise_or(mask,mascaras[k],mask);
	}
	
	return mask;
}
