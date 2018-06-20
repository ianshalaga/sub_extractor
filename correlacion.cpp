#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "string"
#include "pdi_functions.h"
#include "djr_functions.h"

using namespace cv;
using namespace std;
using namespace pdi;

Mat correlacion(const Mat &imagen1,const Mat &imagen2) {
	
	vector<int> metodo = {/*CV_TM_SQDIFF,*/
						  /*CV_TM_SQDIFF_NORMED,*/
						  /*CV_TM_CCORR,*/
						  CV_TM_CCORR_NORMED/*,*/
						  /*CV_TM_CCOEFF,*/
						  /*CV_TM_CCOEFF_NORMED*/};
	
	Mat corr(metodo.size(),1,CV_32F);
	
	Mat imagen1_f,imagen2_f;
	imagen1.convertTo(imagen1_f,CV_32F);
	imagen2.convertTo(imagen2_f,CV_32F);
	
	for(int i=0;i<metodo.size();i++) { 
		Mat corr_met;
		matchTemplate(imagen1_f,imagen2_f,corr_met,metodo[i]);
		corr.at<float>(i,0) = corr_met.at<float>(0,0);  // corr_met solo tiene un pixel
	}
	
	return corr;
}
