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
		
		Histogram h(*it);
		cout << "Debug, in recognition, histogram computed :" << endl;
		cout << h.toString() << endl;
		
		Person qp ("Query", "Person", h);
		
		// Search the closest person in the gallery
		Person closestPerson = g.search(qp);
		
		// Print the distance an the id of the closest person
		std::cout << "FaceRecognition: smallest distance = " 
			  << qp.getHistogram().distance(closestPerson.getHistogram()) << std::endl;
			
		std::cout << "FaceRecognition: closest person is: " << std::endl;
		std::cout << closestPerson.toString() << std::endl;
	}
}

		
