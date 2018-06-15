#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

/****************************************************************/

pair<double,double> xy_media(Mat &imagen) {
	
	double resx = 0.0, resy = 0.0;
	
	int filas = imagen.rows;
	int columnas = imagen.cols;
	
	for(int i=0;i<filas;i++) { 
		for(int j=0;j<columnas;j++) { 
			resx += i*imagen.at<uchar>(i,j);
			resy += j*imagen.at<uchar>(i,j);
		}
	}
	
	double suma = sum(imagen)[0];
	resx /= suma; resy /= suma;
	
	return make_pair(resx,resy);
}

double momento_central(Mat &imagen,int p,int q,pair<double,double> medias) {
	
	double res = 0.0, aux;
	
	int filas = imagen.rows;
	int columnas = imagen.cols;
	
	for(int i=0;i<filas;i++) { 
		for(int j=0;j<columnas;j++) { 
			aux = pow(i - medias.first,p);
			aux *= pow(j - medias.second,q);
			aux *= imagen.at<uchar>(i,j);
			res += aux;
		}
	}
	
	return res;
}

double momento_central_normalizado(Mat &imagen,int p,int q,pair<double, double> medias) {
	double upq = momento_central(imagen,p,q,medias);
	double u00 = sum(imagen)[0];
	u00 = pow(u00, (p+q)/2.0+1);
	return upq/u00;
}

/****************************************************************/

Mat coeficientes_hu(Mat imagen) {
	
	Mat res(7,1,CV_64F);
	
	pair<double,double> par = xy_media(imagen);
	
	double n02 = momento_central_normalizado(imagen,0,2,par);
	double n03 = momento_central_normalizado(imagen,0,3,par);
	double n11 = momento_central_normalizado(imagen,1,1,par);
	double n12 = momento_central_normalizado(imagen,1,2,par);
	double n20 = momento_central_normalizado(imagen,2,0,par);
	double n21 = momento_central_normalizado(imagen,2,1,par);
	double n30 = momento_central_normalizado(imagen,3,0,par);
	
	//phi1:
	double aux = n20 + n02;
	res.at<double>(0,0) = aux;
	
	//phi2:
	aux = pow(n20 - n02, 2) + 4 * pow(n11, 2);
	res.at<double>(1,0) = aux;
	
	//phi3:
	aux = pow(n30 - 3*n12, 2) + pow(3*n21 - n03, 2);
	res.at<double>(2,0) = aux;
	
	//phi4:
	aux = pow(n30 + n12, 2) + pow(n21 + n03, 2);
	res.at<double>(3,0) = aux;
	
	//phi5:
	aux = (n30 - 3*n12)*(n30 + n12)*(pow(n30 + n12, 2) - 3*pow(n21 + n03, 2));
	double aux2 = (3*n21 - n03)*(n21 + n03)* (3*pow(n30 + n12, 2) - pow(n21 + n03, 2));
	aux += aux2;
	res.at<double>(4,0) = aux;
	
	//phi6:
	aux = (n20 - n02)*( pow(n30 + n12, 2) - pow(n21 + n03, 2) );
	aux2 = 4*n11*(n30 + n12)*(n21 + n03);
	aux += aux2;
	res.at<double>(5,0) = aux;
	
	//phi7:
	aux = (3*n21 - n03)*(n30 + n12)*( pow(n30 + n12, 2) - 3*pow(n21 + n03, 2) );
	aux2 = (3*n12 - n30)*(n21 + n03)*( 3*pow(n30 + n12, 2) - pow(n21 + n03, 2) );
	aux += aux2;
	res.at<double>(6,0) = aux;
	
	return res;
}


