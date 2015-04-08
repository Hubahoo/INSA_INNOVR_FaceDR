#include "detection.hpp"
#include "init.hpp"

#include <iostream>

using namespace std;
using namespace cv;

int detectFaces(CvCapture* capture,CascadeClassifier faceCascade,vector<Mat> faces){
	Mat frame= cvQueryFrame(capture);
    vector<Rect> faces_rec;
	if(frame.empty()) return -1;

	Mat frame_gray;
    cvtColor(frame,frame_gray,CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);	

    faceCascade.detectMultiScale( frame_gray, faces_rec, DEF_SCALE, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30,30) );

	for( size_t i = 0; i < faces_rec.size(); i++ ){
        Point start_p(faces_rec[i].x,faces_rec[i].y);
        Point end_p( faces_rec[i].x+faces_rec[i].width, faces_rec[i].y+faces_rec[i].height);
      
     
        rectangle( frame, start_p, end_p, Scalar(0,0,255),1,8);
     
	}
	imshow( "detection", frame );

    waitKey(10);
	return 0;
}