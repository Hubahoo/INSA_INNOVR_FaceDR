#include "detection.hpp"

using namespace std;
using namespace cv;

int detectFaces(CvCapture* capture,CascadeClassifier faceCascade,vector<Mat> faces){

	Mat frame= cvQueryFrame(capture);
	imshow("test",frame);

	waitKey(100);

	return 0;
}