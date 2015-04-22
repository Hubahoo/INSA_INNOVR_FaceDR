#include <iostream>
#include <vector>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "recognition.hpp"

using std::cout;
using std::endl;
using std::vector;

int recognitionFaces(Gallery g, std::vector<cv::Mat> faces)
{
	for(vector<cv::Mat>::iterator it = faces.begin(); it != faces.end(); ++it){
		
		cout << "FaceFramboise: computing the histogram ..." << endl;
		Histogram h(*it);
		//cout << "Debug: in recognitionFaces: histogram:" << endl;
		//cout << h.toString() << endl;
		
		Person qp ("Query", "Person", h);
		
		// Search the closest person in the gallery
		Person closestPerson = g.search(qp);
		
		if (closestPerson.getFirstname() != ""){
			// Print the distance an the id of the closest person
			std::cout << "FaceFramboise: smallest distance = " 
				  << qp.getHistogram().distance(closestPerson.getHistogram()) << endl;
			
			cout << "FaceFramboise: closest person is: " << endl;
			cout << closestPerson.toString() << endl;
		}
		else{
			cout << "Debug: empty database I guess ..." << endl;
		}
	}
}

		
