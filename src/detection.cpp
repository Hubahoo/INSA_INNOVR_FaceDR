#include <iostream>
#include <vector>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "detection.hpp"

#include "define.hpp"

using std::cout;
using std::endl;

int detectFaces(cv::Mat frame, cv::CascadeClassifier faceCascade, std::vector<cv::Mat> &faces)
{
	// Regions Of Interest
	std::vector<cv::Rect> roi;
	
	if(frame.empty()){
		cout << "Error: empty frame" << endl;
		return -1;
	}

	cv::Mat frame_gray;
	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);	
	
	// Detect the faces in the frame
	faceCascade.detectMultiScale(frame_gray, roi, SCALE, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
	faces.clear();

	for(std::vector<cv::Rect>::iterator it = roi.begin(); it != roi.end(); ++it){
	
		cv::Point start_p(it->x, it->y);
		cv::Point end_p(it->x + it->width, it->y + it->height);
		cv::Point center_p(it->x + it->width/2, it->y + it->height/2);
		
		int extraction_width = it->width;
		int extraction_height = (1.2*it->width);

		rectangle(frame, start_p, end_p, cv::Scalar(0,0,255), 1, 8);

		cv::Rect extraction_rect(center_p.x - extraction_width/2, center_p.y - extraction_height/2, extraction_width, extraction_height);

		cv::Mat temp_face(frame_gray, extraction_rect);
		cv::Mat temp_face_resized;
		resize(temp_face, temp_face_resized, cv::Size(130,150));
		
		cv::imshow("detection", temp_face);
		cv::waitKey(2000);
		
		faces.push_back(temp_face_resized);
	}
	
	//cv::imshow("frame", frame);
	//cv::waitKey(2000);

	return 0;
}


