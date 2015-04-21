#include <iostream>

#include "detection.hpp"
#include "init.hpp"


int detectFaces(CvCapture* capture, cv::CascadeClassifier faceCascade, std::vector<cv::Mat> &faces){
	cv::Mat frame= cvQueryFrame(capture);
	std::vector<Rect> faces_rec;
	if(frame.empty()) return -1;

	cv::Mat frame_gray;
	cvtColor(frame,frame_gray,CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);	
	
	faceCascade.detectMultiScale( frame_gray, faces_rec, DEF_SCALE, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30,30) );
	faces.clear();

	for(size_t i = 0; i < faces_rec.size(); i++){
		Point start_p(faces_rec[i].x,faces_rec[i].y);
		Point end_p(faces_rec[i].x+faces_rec[i].width, faces_rec[i].y+faces_rec[i].height);
		Point center_p(faces_rec[i].x+faces_rec[i].width/2, faces_rec[i].y+faces_rec[i].height/2);     
		int extraction_width=faces_rec[i].width;
		int extraction_height=(faces_rec[i].width*1.2);

		rectangle(frame, start_p, end_p, Scalar(0,0,255),1,8);

		Rect extraction_rect(center_p.x-extraction_width/2,center_p.y-extraction_height/2,extraction_width,extraction_height);

		cv::Mat temp_face(frame_gray,extraction_rect);
		cv::Mat temp_face_resized;
		resize(temp_face,temp_face_resized,Size(130,150));
		faces.push_back(temp_face_resized);
	}
	
	imshow("detection", frame);

	waitKey(10);
	return 0;
}


