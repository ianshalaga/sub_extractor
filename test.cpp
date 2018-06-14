#include "iostream"
#include "iomanip"
#include "sstream"
#include "string"
#include "opencv2/opencv.hpp"
#include "djr_functions.h"

using namespace cv;
using namespace std;

void test(VideoCapture video,int cantidad) {
	
	int total_frames = video.get(CV_CAP_PROP_FRAME_COUNT);
	float step = float(total_frames)/cantidad;
	
	vector<Mat> resultados;
	
	for(float K=step/2, i=0; K<total_frames; K+=step, ++i) {
		video.set(CV_CAP_PROP_POS_FRAMES,K);
		Mat frame;
		video >> frame;
		bool sub = detectar_sub(frame,resultados);
		cout<<sub<<"\n";
	}
}
