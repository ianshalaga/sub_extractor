#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

Mat acondicionar(const Mat &mascara) {
	
	int filas = mascara.rows;
	int columnas = mascara.cols;
	
	Mat etiquetas,estadisticas,centroides;
	connectedComponentsWithStats(mascara,etiquetas,estadisticas,centroides);
	etiquetas.convertTo(etiquetas,CV_8UC(1));
	
	Mat acondicionada;
	
	if (estadisticas.rows > 3) {
		int m1 = estadisticas.at<int>(1,4);
		int im1;
		for(int i=2;i<estadisticas.rows;i++) { 
			if (estadisticas.at<int>(i,4) > m1) {
				m1 = estadisticas.at<int>(i,4);
				im1 = i;
			}
		}
		
		int m2 = 0;
		int im2;
		for(int i=1;i<estadisticas.rows;i++) { 
			if (m1 > estadisticas.at<int>(i,4) && estadisticas.at<int>(i,4) > m2) {
				m2 = estadisticas.at<int>(i,4);
				im2 = i;
			}
		}
		
		for(int i=0;i<filas;i++) { 
			for(int j=0;j<columnas;j++) { 
				if (etiquetas.at<uchar>(i,j) == im1)
					etiquetas.at<uchar>(i,j) = 255;
				else if ((etiquetas.at<uchar>(i,j) == im2))
					etiquetas.at<uchar>(i,j) = 255;
				else
					etiquetas.at<uchar>(i,j) = 0;
			}
		}
		
		acondicionada = etiquetas;
	}
	else
		acondicionada = mascara;
	
	return acondicionada;
}
