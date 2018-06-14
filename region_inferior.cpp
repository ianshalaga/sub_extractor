#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "opencv2/video/tracking.hpp"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

Mat region_inferior(const Mat &imagen) {
	
	int filas = imagen.rows;
	int columnas = imagen.cols;
	
	Mat region_interes;
	Rect ROI(0,filas/4*3,columnas,filas/4);
	region_interes = imagen(ROI);
	
	return region_interes;
}
