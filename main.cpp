#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "init.hpp"
#include "detection.hpp"


using namespace	std::cout;
using namespace	std::endl;

//main program, no code must be written here except function calls
//and variables
int main(int argc, char** argv)
{
	CvCapture* capture;
	cv::CascadeClassifier faceCascade;
	std::vector<Mat> faces;
	cv::Mat frame;
	faceCascade.load(DEF_CLASSIFIER);
	capture = cvCaptureFromCAM(0);

	if(init(argc,(const char**)argv,capture,faceCascade))
		return 3;

	while(1){
		detectFaces(capture,faceCascade,faces);
    }

	std::cout << "Succesfully exiting ..." << std::endl;
	return 0;
}


