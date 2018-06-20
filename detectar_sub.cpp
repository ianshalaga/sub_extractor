#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

bool detectar_sub(const Mat &fotograma,vector<Mat> &resultados) {
	
//	true: hay subtitulo; false: no hay subtitulo
	bool subtitulos;
	
//	Region de interes inferior de la imagen donde se encuentran los subtitulos
	Mat inferior = region_inferior(fotograma);
	
//	Separacion en canales HSV
	Mat inferior_hsv;
	vector<Mat> inferior_hsv_vec;
	cvtColor(inferior,inferior_hsv,CV_BGR2HSV);
	split(inferior_hsv,inferior_hsv_vec);
	
	Mat inferiorV = inferior_hsv_vec[2];
	
//	Reduccion de ruido
	Mat inferiorV_gauss;
	GaussianBlur(inferiorV,inferiorV_gauss,{3,3},0,0,BORDER_DEFAULT);
	
//	Deteccion de bordes
	Mat filtradaV = convolve(inferiorV_gauss,kernelPA0());
	
//	Eliminar contornos de las imagenes de bordes
	filtradaV = limpiar_contorno(filtradaV,1);
	
//	Binarizacion de bordes
	Mat filtradaV_u;
	int columnas_inf = inferior.cols;
	threshold(filtradaV,filtradaV_u,inter_umbral(columnas_inf),255,THRESH_BINARY);
	
//	Rellenado del texto
	Mat cierre;
	Mat ee_rect = getStructuringElement(MORPH_RECT,{3,3},Point(-1,-1));
	morphologyEx(filtradaV_u,cierre,MORPH_CLOSE,ee_rect,Point(-1,-1),5);
	
//	Reduccion de ruido
	Mat cierre_med;
	medianBlur(cierre,cierre_med,3);
	
	Mat apertura1;
	Mat ee_v1 = Mat::ones(columnas_inf/80,1,CV_8UC(1));
	morphologyEx(cierre_med,apertura1,MORPH_OPEN,ee_v1,Point(-1,-1),1);

	Mat apertura2;
	Mat ee_h1 = Mat::ones(1,columnas_inf/80,CV_8UC(1));
	morphologyEx(cierre_med,apertura2,MORPH_OPEN,ee_h1,Point(-1,-1),1);
	
//	Mascara de texto
//	Mat inferior_mask;
//	bitwise_or(apertura1,apertura2,inferior_mask);
	
//	Dilatacion horizontal
	Mat ee_h2 = Mat::ones(1,columnas_inf,CV_8UC(1));
	dilate(apertura1,apertura1,ee_h2,Point(-1,-1),1);
	
//	Dilatacion vertical
	Mat ee_v2 = Mat::ones(columnas_inf,1,CV_8UC(1));
	dilate(apertura2,apertura2,ee_v2,Point(-1,-1),1);
	
//	Transformada de Hough
	vector<Vec2f> lineas;
	HoughLines(apertura1,lineas,1,CV_PI/2,columnas_inf*0.15);
	
//	Lineas de deteccion
	Mat inferior_gris;
	cvtColor(inferior,inferior_gris,CV_BGR2GRAY);
	Mat lineas_sub = lineas_hough(inferior_gris,lineas);
	
//	Comprobacion de existencia de subtitulo
	Rect roi;
	Mat inferior_roi = inferior.clone();
	Mat inferior_mask(inferior.size(),CV_8UC(1),Scalar(0));
	Mat inferior_tesseract(inferior.size(),CV_8UC(1),Scalar(0));
	Mat inferior_lleno;
	
	if (lineas.size() == 0)
		subtitulos = false;
	else {
		subtitulos = true;
		
		//	Ajuste de region especifica del subtitulo
		Mat promedio_h = promedio_intensidad_h(apertura1);
		Mat promedio_v = promedio_intensidad_v(apertura2);
		threshold(promedio_v,promedio_v,0,255,THRESH_BINARY|THRESH_OTSU);
		threshold(promedio_h,promedio_h,0,255,THRESH_BINARY|THRESH_OTSU);
		vector<int> blancosV = blancos_v(promedio_h);
		vector<int> blancosH = blancos_h(promedio_v);
		
		int limite_izquierdo = blancosH[0];
		int limite_derecho = blancosH[blancosH.size()-1]-blancosH[0];
		int limite_superior = blancosV[0];
		int limite_inferior = blancosV[blancosV.size()-1]-blancosV[0];
		
		roi = Rect(limite_izquierdo,limite_superior,limite_derecho,limite_inferior);
		rectangle(inferior_roi,roi,Scalar(0,255,0),3,8,0);
		
		//	Crea y aplica la mascara para usar con tesseract
		inferior_mask(roi).setTo(Scalar(255));
		Mat ee_rect_mask = getStructuringElement(MORPH_RECT,{columnas_inf/80,columnas_inf/80},Point(-1,-1));
		dilate(inferior_mask,inferior_mask,ee_rect_mask,Point(-1,-1),1);
		
//		inferior.copyTo(inferior_tesseract,inferior_mask);
		inferior_tesseract = inferior(roi);
	}
	
	/*Muestra los resultados parciales*/
//	[0]  fotograma: fotograma de trabajo.
//	[1]  inferior: cuarto inferior del fotograma de trabajo.
//	[2]  inferiorV: canal V de la parte inferior.
//	[3]  inferiorV_gauss: canal V afectado por desenfoque gaussiano.
//	[4]  filtradaV: bordes de la parte inferior.
//	[5]  filtradaV_u: bordes binarizados de la parte inferior.
//	[6]  cierre: rellenado de bordes.
//	[7]  cierre_med: reduccion de ruido mediante mediana
//	[8]  apertura1: acondicionamiento final para la deteccion de lineas horizontales.
//	[9]  apertura2: acondicionamiento final para la deteccion de lineas verticales.
//	[10] lineas_sub: lineas sobre la parte inferior en escala de grises.
//	[11] inferior_roi: subtitulo encuadrado.
//	[12] inferior_mask: mascara para extraer el texto del fotograma
//	[13] inferior_tesseract: solo texto del fotograma
	resultados = {fotograma,inferior,inferiorV,inferiorV_gauss,filtradaV,filtradaV_u,cierre,cierre_med,apertura1,apertura2,lineas_sub,inferior_roi,inferior_mask,inferior_tesseract};
	vector<Mat> to_ocr = {inferior_tesseract};
	Mat mosaico_res = concatenar_imagenes(to_ocr,true,true);
	
//	namedWindow("Resultados",CV_WINDOW_KEEPRATIO);
//	imshow("Resultados",mosaico_res);
//	waitKey();
	/**/
	
	/*Guarda los resultados parciales*/
//	srand (time(NULL));
//	int v = rand() % 1000;
//	stringstream s;
//	s << "resultado" << v << ".png";
//	imwrite(s.str(),mosaico_res);
	/**/
	
	return subtitulos;
}
