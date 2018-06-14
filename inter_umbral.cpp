#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

int inter_umbral(int columnas) {
	
	if (columnas < 640)
		columnas = 640;
	if (columnas > 1920)
		columnas = 1920;
	
	float a = (-1.0*127)/1280;
	float b = float(635)/2;
	
	int umbral = a*columnas + b;
	
	return umbral;
}
