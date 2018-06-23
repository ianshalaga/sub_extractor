#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

Mat srt2img(string nombre_archivo,Mat solucion,double tiempo_fotograma) {
	
	ifstream archivo_srt (nombre_archivo);
	
	string id;
	int horas;
	int minutos;
	int segundos;
	int milisegundos;
	string flechita;
	char separador;
	
	while (archivo_srt >> id) {
		
		archivo_srt >> horas >> separador >> minutos >> separador >> segundos >> separador >> milisegundos;
		double tms1 = hms2ms(horas,minutos,segundos,milisegundos);
		int inicio = tms1/tiempo_fotograma;
		
		archivo_srt >> flechita;
		
		archivo_srt >> horas >> separador >> minutos >> separador >> segundos >> separador >> milisegundos;
		double tms2 = hms2ms(horas,minutos,segundos,milisegundos);
		int fin = tms2/tiempo_fotograma;
		
		for(int i = inicio;i<fin+1;i++) { 
			solucion.at<uchar>(0,i) = 255;
		}
		
		archivo_srt.ignore();
		
		string linea;
		while (getline(archivo_srt,linea)) {
			if (linea.empty())
				break;
		}
	}
	
	return solucion;
}
