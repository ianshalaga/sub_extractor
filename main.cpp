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
	Mat imagen1 = imread("img/thumb0033.jpg");
	Mat imagen2 = imread("img/thumb0246.jpg");
	Mat imagen3 = imread("img/vlcsnap-2018-05-20-00h37m14s939.png");
	Mat imagen4 = imread("img/y1.png");
	Mat imagen5 = imread("img/y2.png");
	Mat imagen6 = imread("img/thumb0346.jpg");
	Mat imagen7 = imread("img/fotograma010.jpg");
	Mat imagen8 = imread("img/fotograma204.jpg");
	Mat imagen9 = imread("img/fotograma046.jpg");
	Mat imagen10 = imread("img/fotograma056.jpg");
	Mat imagen11 = imread("img/vlcsnap-2018-05-20-00h37m10s543.png");	
	Mat imagen12 = imread("img/thumb0344.jpg");
	Mat imagen13 = imread("img/fotograma178.jpg");
	Mat imagen14 = imread("img/thumb0342.jpg");
////	
	vector<Mat> resultados_ant;
	vector<Mat> resultados_act;
//	vector<Mat> imagenes = {imagen1,imagen2,imagen3,imagen4,imagen5,imagen6,imagen7,imagen8,imagen9,imagen10,imagen11,imagen12,imagen13};
	vector<Mat> imagenes = {imagen6,imagen12,imagen14,imagen6};

	bool subtitulos = detectar_sub(imagenes[0],resultados_ant);
	
	for(int i=1;i<imagenes.size();i++) { 
		subtitulos = detectar_sub(imagenes[i],resultados_act);
		if (subtitulos == true) {
			cout<<correlacion(resultados_ant[7],resultados_act[7])<<endl;
			vector<Mat> comp = {resultados_ant[7],resultados_act[7]};
			Mat mosaico_comp = concatenar_imagenes(comp,true,true);
			namedWindow("Comparacion",CV_WINDOW_KEEPRATIO);
			imshow("Comparacion",mosaico_comp);
			waitKey();
			resultados_ant = resultados_act;
		}
//		cout<<subtitulos<<"\n";
	}
	
//	VideoCapture video("videos/snk.mp4");
//	test(video,100);
	
//	Mat prom = fotograma_promedio(video);
	
//	Mat res;
//	addWeighted(imagen1,0.5,imagen2,0.5,0,res,CV_8UC(1));
//	imwrite("res.png",prom);
	
	return 0;
} 
