#ifndef DJR_FUNCTIONS_H
#define DJR_FUNCTIONS_H
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "pdi_functions.h"
#include "opencv2/video/tracking.hpp"

// Cuarto inferior de la imagen
cv::Mat region_inferior(const cv::Mat &imagen);

// Concatena imagenes
cv::Mat concatenar_imagenes(std::vector<cv::Mat> imagenes,const bool &color,const bool &vertical);

// Detecta si existe subtitulo en la parte inferior de un fotograma
bool detectar_sub(const cv::Mat &fotograma,std::vector<cv::Mat> &resultados);

// Kernel pasa-altos de suma cero para bordes horizontales
cv::Mat kernelPA0();

// Elimina el marco de la imagen
cv::Mat limpiar_contorno(cv::Mat imagen,int pixeles);

// Dibuja lineas de Hough
cv::Mat lineas_hough(const cv::Mat &bordes,const std::vector<cv::Vec2f> &rho_tita);

void test(cv::VideoCapture video,int cantidad);

// Calcula el valor apropiado del umbral segun el tamaño del fotograma
int inter_umbral(int columnas);

// Posiciones de inicio y fin de los blancos de un perfil vertical
std::vector<int> blancos_h(cv::Mat perfil_v);

// Posiciones de inicio y fin de los blancos de un perfil horizontal
std::vector<int> blancos_v(cv::Mat perfil_h);

// Promedios horizontales de intensidad
cv::Mat promedio_intensidad_h(const cv::Mat &imagen);

// Promedios verticales de intensidad
cv::Mat promedio_intensidad_v(const cv::Mat &imagen);

// Coeficiente de correlacion entre dos imagenes
cv::Mat correlacion(const cv::Mat &imagen1,const cv::Mat &imagen2);

// Conversion del tiempo en ms al formato hh:mm:ss,sss del .srt
std::string ms2hms(const double &tiempo_ms);

// Convercion de imagen a texto (uso de tesseract)
std::string img2str(std::string fotograma_inf);

// Convierte el subtitulo srt original (solucion) a una imagen binaria para la medicion por solapamiento
cv::Mat srt2img(std::string nombre_archivo);

#endif
