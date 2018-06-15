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

// Kernel pasa-altos de 3x3 en cruz
cv::Mat filtro_pa_cruz();

// Kernel pasa-altos de 3x3 en equis
cv::Mat filtro_pa_x();

// Union de mascaras
cv::Mat or_mascaras(const std::vector<cv::Mat> &mascaras);

// Elemento estructurante horizontal
cv::Mat elemento_estructurante_h();

// Elemento estructurante vertical
cv::Mat elemento_estructurante_v();

// Dibuja lineas de Hough
cv::Mat lineas_hough(const cv::Mat &bordes,const std::vector<cv::Vec2f> &rho_tita);

cv::Mat acondicionar(const cv::Mat &mascara);

void test(cv::VideoCapture video,int cantidad);

// Promedio de los frames de un video
cv::Mat fotograma_promedio(cv::VideoCapture video);

// Error cuadratico medio
float ecm(const cv::Mat &imagen1,const cv::Mat &imagen2);

// Calcula el valor apropiado del umbral segun el tamaño del fotograma
int inter_umbral(int columnas);

// Kernel gaussiano cuadrado
cv::Mat gauss_kernel(const int &dimension,const float &stdev);

// Posiciones de inicio y fin de los blancos de un perfil vertical
std::vector<int> blancos_h(cv::Mat perfil_v);

// Posiciones de inicio y fin de los blancos de un perfil horizontal
std::vector<int> blancos_v(cv::Mat perfil_h);

// Promedios horizontales de intensidad
cv::Mat promedio_intensidad_h(const cv::Mat &imagen);

// Promedios verticales de intensidad
cv::Mat promedio_intensidad_v(const cv::Mat &imagen);

// Coeficientes de Hu para comparar el grado de parecido de dos imagenes
cv::Mat coeficientes_hu(cv::Mat imagen);

// Coeficiente de correlacion entre dos imagenes
float correlacion(const cv::Mat &imagen1,const cv::Mat &imagen2);

#endif
