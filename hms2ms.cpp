#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

double hms2ms(int horas,int minutos,int segundos,int milisegundos) {
	
	double h = horas * 3600000;
	double m = minutos * 60000;
	double s = segundos * 1000;
	double ms = milisegundos;
	
	double tms = h+m+s+ms;
	
	return tms;
}
