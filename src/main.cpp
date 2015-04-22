#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "detection.hpp"
#include "recognition.hpp"

#include "Gallery.hpp"

#include "define.hpp"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	cout << "FaceFramboise: start" << endl;
	cout << "FaceFramboise: initialization" << endl;
	
	cv::CascadeClassifier faceCascade;
	if(!faceCascade.load(CLASSIFIER)){
		cout << "FaceFramboise: error when loading the classifier" << endl;
		return -1;
	}
	
	cv::Mat frame;
	std::vector<cv::Mat> faces;
	
	cout << "FaceFramboise: loading the faces database ..." << endl;
	Gallery gallery; // Load the database of the known faces in a Gallery object
	cout << "Debug : gallery loaded" << endl;
	if(argc == 1){
		while(1){
			// Load the image from the camera
			//frame = capture();
			//detectFaces();
			//recognitionFaces();
		}
	}
	else if(argc == 2){
		// Load the image
		frame = cv::imread(argv[1]);
		cout << "FaceFramboise: image loaded" << endl;
		
		/*
		cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
		imshow("Display window", frame);
		cv::waitKey(0);*/
		
		cout << "FaceFramboise: detecting the faces ..." << endl;
		detectFaces(frame, faceCascade, faces);
		
		cout << "FaceFramboise: recognition of the faces ..." << endl;
		recognitionFaces(gallery, faces);
	}
	else{
		cout << "FaceFramboise: too many arguments" << endl;
	}

	cout << "FaceFramboise: exit" << endl;
	return 0;
}


