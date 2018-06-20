#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

string img2str(string fotograma_inf) {
	
	/*OCR*/
	stringstream s;
	s << "tesseract " << fotograma_inf << " output " << "nobatch letras";
	system(s.str().c_str());
	
	ifstream subs_fotograma ("output.txt");
	string linea, resultado;
	while (getline(subs_fotograma,linea)) {
		if (not linea.empty())
			resultado += linea + '\n';
	}
//	stringstream buffer;
//	buffer << subs_fotograma.rdbuf();
	/*OCR*/
	
//	return buffer.str();
	return resultado;
}
