#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

int main(int argc, char** argv) {
	
//	Carga de imagenes
//	Mat imagen1 = imread("img/thumb0033.jpg");
//	Mat imagen2 = imread("img/thumb0246.jpg");
//	Mat imagen3 = imread("img/vlcsnap-2018-05-20-00h37m14s939.png");
//	Mat imagen4 = imread("img/y1.png");
//	Mat imagen5 = imread("img/y2.png");
//	Mat imagen6 = imread("img/thumb0346.jpg");
//	Mat imagen7 = imread("img/fotograma010.jpg");
//	Mat imagen8 = imread("img/fotograma204.jpg");
//	Mat imagen9 = imread("img/fotograma046.jpg");
//	Mat imagen10 = imread("img/fotograma056.jpg");
//	Mat imagen11 = imread("img/vlcsnap-2018-05-20-00h37m10s543.png");	
//	Mat imagen12 = imread("img/thumb0344.jpg");
//	Mat imagen13 = imread("img/fotograma178.jpg");
//	Mat imagen14 = imread("img/thumb0342.jpg");

//	vector<Mat> imagenes = {imagen1,imagen2,imagen3,imagen4,imagen5,imagen6,imagen7,imagen8,imagen9,imagen10,imagen11,imagen12,imagen13};
//	vector<Mat> imagenes = {imagen1,imagen5};
	
//	vector<Mat> resultados_ant;
//	vector<Mat> resultados_act;
//	
//	bool subtitulos = detectar_sub(imagenes[0],resultados_ant);
	
//	for(int i=1;i<imagenes.size();i++) { 
//		subtitulos = detectar_sub(imagenes[i],resultados_act);
//		if (subtitulos == true) {
//			Mat corr = correlacion(resultados_ant[7],resultados_act[7]);
//			cout<<corr.at<float>(3,0)<<endl<<endl;
			
			/*OCR*/
//			ofstream subs_fotograma ("prueba_tesseract/subs_fotograma.txt");
//			
//			for(int j=0;j<resultados_act.size();j++) {
//				stringstream s1;
//				s1 << "prueba_tesseract/fotograma" << j << ".png";
//				imwrite(s1.str(),resultados_act[j]);
//				subs_fotograma<<s1.str()<<endl;
//			}
//			
//			stringstream s2;
//			s2 << "tesseract " << "prueba_tesseract/subs_fotograma.txt" << " output" << i;
//			system(s2.str().c_str());
			/*OCR*/
			
//			vector<Mat> comp = {resultados_ant[7],resultados_act[7]};
//			Mat mosaico_comp = concatenar_imagenes(comp,true,true);
//			namedWindow("Comparacion",CV_WINDOW_KEEPRATIO);
//			imshow("Comparacion",mosaico_comp);
//			waitKey();
//			resultados_ant = resultados_act;
//		}
//		cout<<subtitulos<<"\n";
//	}
	
//	Carga del video
	stringstream s_video,s_v1;
	s_video << "snk_Sony AVC-MVC_SNK_720[11]";
	s_v1 << "videos/" << s_video.str() << ".mp4";
	VideoCapture video(s_v1.str());
	
	int total_frames = video.get(CV_CAP_PROP_FRAME_COUNT);
	
//	Archivo .srt de subtitulos
	stringstream s_a;
	s_a << s_video.str() << ".srt";
	ofstream archivo_subs (s_a.str());
	
//	Primera fotograma
	video.set(CV_CAP_PROP_POS_FRAMES,0);
	Mat frame_ant;
	video >> frame_ant;
	
	vector<Mat> resultados_ant;
	bool subs_ant = detectar_sub(frame_ant,resultados_ant);
	
//	Variables usadas
	int cont_srt = 1;
//	Mat suma;
//	int cont_iguales = 0;
	
//	Resto de los fotogramas
	for(int f=1;f<total_frames;f++) {
		
		cout<<"fotograma"<<f<<endl;
		
		double tiempo = video.get(CV_CAP_PROP_POS_MSEC);
		
		video.set(CV_CAP_PROP_POS_FRAMES,f);
		Mat frame;
		video >> frame;
		
		vector<Mat> resultados_act;
		bool subs_act = detectar_sub(frame,resultados_act);
		
		if (subs_act == true) { // si hay subtitulos
			if (subs_ant == false) { // si hay subtitulos pero antes no habia
				stringstream s_srt1;
				s_srt1 << cont_srt << endl << tiempo << " --> ";
				archivo_subs << s_srt1.str();
//				suma = resultados_act[1].clone();
//				cont_iguales++;
				cont_srt++;
			} else { // si hay subtitulos y antes habia
				Mat corr = correlacion(resultados_ant[7],resultados_act[7]);
				if (corr.at<float>(0,0) < 0.9) { // si hay subtitulos y antes habia pero eran distintos
//					Mat promedio = suma/cont_iguales;
//					cont_iguales = 0;
					stringstream s_srt2;
					s_srt2 << tiempo << endl << "A" << endl << endl << cont_srt << endl << tiempo << " --> ";
					archivo_subs << s_srt2.str();
					cont_srt++;
				} else { // si hay subtitulos y antes habia y son los mismo
//					suma += resultados_act[1];
//					cont_iguales++;
				}
			}
			
		} else { // si no hay subtitulos
			if (subs_ant == true) { // si no hay subtitulos pero antes habia
//				Mat promedio = suma/cont_iguales;
//				cont_iguales = 0;
				stringstream s_srt3;
				s_srt3 << tiempo << endl << "A" << endl << endl;
				archivo_subs << s_srt3.str();
				cont_srt++;
			}
		} // end if de verificacion de subtitulos
		
		resultados_ant = resultados_act;
	} // end for que recorre los fotogramas
	
//	test(video,100);
	
//	Mat res;
//	addWeighted(imagen1,0.5,imagen2,0.5,0,res,CV_8UC(1));
//	imwrite("res.png",prom);
	
	return 0;
} 
