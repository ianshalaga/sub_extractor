#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"

using namespace std;
using namespace pdi;
using namespace cv;

float ecm(const Mat &imagen1,const Mat &imagen2) {
	
	Mat imagen2_redim;
	resize(imagen2,imagen2_redim,imagen1.size(),0,0,CV_INTER_LINEAR);
	
	int filas = imagen1.rows;
	int columnas = imagen1.cols;
	int cantidad = filas*columnas;
	
	double suma = 0;
	
	for(int i=0;i<filas;i++) { 
		for(int j=0;j<columnas;j++) { 
			suma += pow((imagen1.at<double>(i,j)-imagen2_redim.at<double>(i,j)),2);
		}
	}
	
	return suma/cantidad;
}
