#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"
#include "vector"

using namespace std;
using namespace pdi;
using namespace cv;

vector<int> blancos_v(Mat perfil_h) {
	
	int filas = perfil_h.rows;
	bool contar = true;
	int numero = 0;
	
	for (int i=0;i<filas;i++) {
		if (perfil_h.at<uchar>(i,0) == 255 && contar == true) {
			numero = numero + 1;
			contar = false;
		}
		else if (perfil_h.at<uchar>(i,0) == 0 && contar == false)
			contar = true;
	}
	
	vector<int> posiciones(numero*2);
	
	if (perfil_h.at<uchar>(filas-1,0) == 255)
		posiciones[numero*2-1] = filas-1;
	
	contar = true;
	int c = 0;
	
	for (int i=0;i<filas;i++) {
		if (perfil_h.at<uchar>(i,0) == 255 && contar == true) {
			posiciones[c] = i;
			contar = false;
			c = c+1;
		}
		else if (perfil_h.at<uchar>(i,0) == 0 && contar == false) {
			contar = true;
			posiciones[c] = i-1;
			c = c+1;
		}
	}
	
	return posiciones;
}
