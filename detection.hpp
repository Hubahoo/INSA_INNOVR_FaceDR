#ifndef _DETECTION_HPP_INCLUDED
#define _DETECTION_HPP_INCLUDED

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

int detectFaces(CvCapture* capture,CascadeClassifier faceCascade,vector<Mat> &faces);

#endif //_DETECTION_HPP_INCLUDED
