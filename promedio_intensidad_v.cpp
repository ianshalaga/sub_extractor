#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
//#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

Mat promedio_intensidad_v(const Mat &imagen) {
	
	int filas = imagen.rows;
	int columnas = imagen.cols;
	
	Mat vector_fila(1,columnas,CV_8UC(1),Scalar(0));
	
	for(int j=0;j<columnas;j++) { 
		int suma = 0;
		for(int i=0;i<filas;i++) { 
			suma += imagen.at<uchar>(i,j);
		}
		vector_fila.at<uchar>(0,j) = suma/filas;
	}

	return vector_fila;
}
