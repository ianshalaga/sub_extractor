#include "iostream"
#include "iomanip"
#include "sstream"
#include "string"
#include "opencv2/opencv.hpp"
#include "djr_functions.h"

using namespace cv;
using namespace std;

Mat fotograma_promedio(VideoCapture video) {
	
	int total_frames = video.get(CV_CAP_PROP_FRAME_COUNT);
	
	video.set(CV_CAP_PROP_POS_FRAMES,0);
	Mat promedio;
	video >> promedio;
	promedio.convertTo(promedio,CV_64F); 
	
	for(int i=1;i<1000;i++) {
		video.set(CV_CAP_PROP_POS_FRAMES,i);
		Mat frame;
		video >> frame;
		frame.convertTo(frame,CV_64F);
		promedio = promedio + frame;
		cout<<"fotograma "<<i<<"\n";
	}
	
	return promedio/1000;
}
