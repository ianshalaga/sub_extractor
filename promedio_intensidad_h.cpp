#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
//#include "djr_functions.h"

using namespace std;
using namespace pdi;
using namespace cv;

Mat promedio_intensidad_h(const Mat &imagen) {
	
	int filas = imagen.rows;
	int columnas = imagen.cols;
	
	Mat vector_columna(filas,1,CV_8UC(1),Scalar(0));
	
	for(int i=0;i<filas;i++) { 
		int suma = 0;
		for(int j=0;j<columnas;j++) { 
			suma += imagen.at<uchar>(i,j);
		}
		vector_columna.at<uchar>(i,0) = suma/columnas;
	}
	
	return vector_columna;
}
