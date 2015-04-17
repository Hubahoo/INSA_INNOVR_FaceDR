#include <stdio.h>
#include <iostream>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Histogram.hpp"
#include "Gallery.hpp"
#include "Person.hpp"


int main (int argc, char *argv[])
{
	std::cout << "FaceRecognition: start" << std::endl;

	if (argc == 2){
		cv::Mat image = cv::imread(argv[1],0);

		if (image.rows == 150 && image.cols == 130){
			std::cout << "FaceRecognition: correct size of the image" << std::endl;
			
			Histogram h(image);

			Person p("700", "fa", h);
			
			Gallery gallery; // Load the database of the known faces in a Gallery object
			
			gallery.addToDatabase(p);
			
			// Serialization of the histogram in a stringstream
			/*std::stringstream ss;
			{
				boost::archive::text_oarchive oa(ss);
				oa << h;
			}
			std::cout << ss.str() << std::endl;
			*/
			
			// Serialization of the histogram in a fstream
			/*
			std::fstream fs("serializationFile", std::ios::out);
			{
				boost::archive::text_oarchive oa(fs);
				oa << h;
			}*/
			
			/*
			Person closestPerson = gallery.search(p); //Research the closest person in the gallery
			//print the distance an the id of the closest person
			std::cout << "FaceRecognition: smallest distance = " 
				  << p.getHistogram().distance(closestPerson.getHistogram()) << std::endl;
			
			std::cout << "FaceRecognition: closest person is: " << std::endl;
			std::cout << closestPerson.toString() << std::endl;*/
		}
		else{
			std::cout << "Error: wrong size of the image" << std::endl;
		}
	}
	else {
		std::cout << "Error: too many arguments" << std::endl;
	}

	std::cout << "FaceRecognition: end" << std::endl;
	return 0;
}
