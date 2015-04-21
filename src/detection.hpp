#ifndef _DETECTION_HPP_INCLUDED
#define _DETECTION_HPP_INCLUDED

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


int detectFaces(CvCapture* capture, cv::CascadeClassifier faceCascade, std::vector<cv::Mat> &faces);

#endif //_DETECTION_HPP_INCLUDED

