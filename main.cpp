#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

int main(int argc, char** argv) {
	
////	Carga del video
//	stringstream s_video,s_v1;
//	s_video << "snk_Sony AVC-MVC_SNK_720[7]";
//	s_v1 << "videos/" << s_video.str() << ".mp4";
//	VideoCapture video(s_v1.str());
//	
//	int total_frames = video.get(CV_CAP_PROP_FRAME_COUNT);
//	
////	Archivo .srt de subtitulos
//	stringstream s_a;
//	s_a << s_video.str() << ".srt";
//	ofstream archivo_subs (s_a.str());
//	
////	Primer fotograma
//	Mat prediccion(1,total_frames,CV_8UC(1),Scalar(0)); // para dice y jaccard
//	
//	Mat frame_ant;
//	video >> frame_ant;
//	
//	double tiempo = video.get(CV_CAP_PROP_POS_MSEC);
//	string tiempo_str = ms2hms(tiempo);
//	
//	vector<Mat> resultados_ant;
//	bool subs_ant = detectar_sub(frame_ant,resultados_ant);
//	
//	int cont_srt = 0;
//	
//	if (subs_ant == true) {
//		prediccion.at<uchar>(0,0) = 255;
//		cont_srt++;
//		stringstream s_srt0;
//		s_srt0 << cont_srt << endl << tiempo_str << " --> ";
//		archivo_subs << s_srt0.str();
//		//				suma = resultados_act[1].clone();
//		//				cont_iguales++;
//	}
//	
////	Variables usadas
//	Mat suma(frame_ant.size(),CV_64FC(3),Scalar(0.0,0.0,0.0));
//	suma = region_inferior(suma);
//	int cont_iguales = 0;
//	
////	Resto de los fotogramas
//	int f;
//	for(f=1;f<total_frames;f++) {
//		
//		cout<<"fotograma"<<f<<endl;
//		
//		Mat frame;
//		video >> frame;
//		
//		if (frame.empty()) break;
//		
//		tiempo = video.get(CV_CAP_PROP_POS_MSEC);
//		tiempo_str = ms2hms(tiempo);
//		
//		vector<Mat> resultados_act;
//		bool subs_act = detectar_sub(frame,resultados_act);
//		
//		if (subs_act == true) { // si hay subtitulos
//			prediccion.at<uchar>(0,f) = 255;
//			if (subs_ant == false) { // si hay subtitulos pero antes no habia
//				cont_srt++;
//				stringstream s_srt1;
//				s_srt1 << cont_srt << endl << tiempo_str << " --> ";
//				archivo_subs << s_srt1.str();
//				subs_ant = true;
//			} else { // si hay subtitulos y antes habia
//				Mat corr = correlacion(resultados_ant[7],resultados_act[7]);
//				if (corr.at<float>(0,0) < 0.9) { // si hay subtitulos y antes habia pero eran distintos
//					Mat promedio = suma/cont_iguales;
//					promedio.convertTo(promedio,CV_8UC(3),255);
//					stringstream s_tess;
//					s_tess << "promedio" << cont_srt << ".jpg";
//					imwrite(s_tess.str(),promedio);
//					string texto = img2str(s_tess.str());
//					suma = 0.0;
//					cont_iguales = 0;
//					
//					cont_srt++;
//					stringstream s_srt2;
//					s_srt2 << tiempo_str << endl << texto << endl << endl << cont_srt << endl << tiempo_str << " --> ";
//					archivo_subs << s_srt2.str();
//					subs_ant = true;
//				} else { // si hay subtitulos y antes habia y son los mismo
//					Mat inferior_f;
//					resultados_act[1].convertTo(inferior_f,CV_64FC(3),1.0/255);
//					pow(inferior_f,2,inferior_f);
//					suma += inferior_f;
//					cont_iguales++;
//					subs_ant = true;
//				}
//			}
//		} else if (subs_ant == true) { // si no hay subtitulos pero antes habia
//			Mat promedio = suma/cont_iguales;
//			promedio.convertTo(promedio,CV_8UC(3),255);
//			stringstream s_tess;
//			s_tess << "promedio" << cont_srt << ".jpg";
//			imwrite(s_tess.str(),promedio);
//			string texto = img2str(s_tess.str());
//			suma = 0.0;
//			cont_iguales = 0;
//			
//			stringstream s_srt3;
//			s_srt3 << tiempo_str << endl << texto << endl << endl;
//			archivo_subs << s_srt3.str();
//			subs_ant = false;
//		}
//		
//		resultados_ant = resultados_act;
//		
//	} // end for que recorre los fotogramas
//	
//	if (subs_ant == true) { //para cuando hay subtitulos en el ultimo fotograma
//		prediccion.at<uchar>(0,f) = 255;
//		Mat promedio = suma/cont_iguales;
//		promedio.convertTo(promedio,CV_8UC(3),255);
//		stringstream s_tess;
//		s_tess << "promedio" << cont_srt << ".jpg";
//		imwrite(s_tess.str(),promedio);
//		string texto = img2str(s_tess.str());
//		suma = 0.0;
//		cont_iguales = 0;
//		
//		stringstream s_srt4;
//		s_srt4 << tiempo_str << endl << texto << endl << endl;
//		archivo_subs << s_srt4.str();
//	} 
//	
////	Medidas de solapamiento (Dice/F1-Score,Jaccard/Intersection over Union)
//	imwrite("prediccion.png",prediccion);
//	
//	Mat solucion(1,total_frames,CV_8UC(1),Scalar(0)); // para dice y jaccard
////	solucion = img2str("Shingeki no Kyojin S2 - 06 [1080p] [MX-EN-PT] [EF3BC295]_track3_spa.srt");
	
	ifstream archivo_srt("Shingeki no Kyojin S2 - 06 [1080p] [MX-EN-PT] [EF3BC295]_track3_spa.srt");
	
	string id;
	int horas;
	int minutos;
	int segundos;
	int milisegundos;
	string flechita;
	char separador;
	while (archivo_srt >> id) {
		archivo_srt >> horas >> separador >> minutos >> separador >> segundos >> separador >> milisegundos;
		archivo_srt >> flechita;
		archivo_srt >> horas >> separador >> minutos >> separador >> segundos >> separador >> milisegundos;
		archivo_srt.ignore();
		string linea;
		while (getline(archivo_srt,linea)) {
			if (linea.empty())
				break;
		}
		cout<<id<<'\n';
	}
	
	return 0;
} 
