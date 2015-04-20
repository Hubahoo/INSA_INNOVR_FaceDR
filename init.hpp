#ifndef _INIT_HPP_INCLUDED
#define _INIT_HPP_INCLUDED

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#define DEF_CLASSIFIER "haarcascades/haarcascade_frontalface_alt2.xml"
#define DEF_SCALE 1.2

bool init(const int &argc, const char** argv, CvCapture* capture, CascadeClassifier &faceCascade);

bool initArgs(const int &argc, const char** argv, CascadeClassifier &faceCascade);

bool initCapture(CvCapture* capture);

#endif //_INIT_HPP_INCLUDED

