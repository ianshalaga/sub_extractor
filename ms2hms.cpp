#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

string ms2hms(const double &tiempo_ms) {
	
	stringstream tiempo_hms;
	
	double tiempo_h = tiempo_ms/3600000;
	int tiempo_ht = tiempo_h;
	
	double tiempo_m = (tiempo_h-tiempo_ht)*60;
	int tiempo_mt = tiempo_m;
	
	double tiempo_s = (tiempo_m-tiempo_mt)*60;
	int tiempo_st = tiempo_s;
	
	double tiempo_ms2 = (tiempo_s-tiempo_st)*1000;
	int tiempo_ms2t = tiempo_ms2;
	
	tiempo_hms << setfill('0') << setw(2) << tiempo_ht << ":" << setfill('0') << setw(2) << tiempo_mt << ":" << setfill('0') << setw(2) << tiempo_st << "," << setfill('0') << setw(3) << tiempo_ms2t;
	
	return tiempo_hms.str();
}
