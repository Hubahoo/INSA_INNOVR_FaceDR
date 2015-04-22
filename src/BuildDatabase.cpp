#include "iostream"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Gallery.hpp"
#include "Person.hpp"
#include "Histogram.hpp"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	cout << "BuildDatabase: start" << endl;
	
	if(argc == 2){
		cv::Mat image = cv::imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); // load and convert to grey level
		
		if (image.rows == 150 && image.cols == 130){
			cout << "BuildDatabase: correct size of the image" << endl;
			
			Histogram h(image);
			Person p("700", "fa", h);
			
			Gallery g;
			//cout << g.toString() << endl;
			g.addToDatabase(p);
		}
		else{
			cout << "BuildDatabase: wrong size of the image" << endl;
		}
	}
	else{
		cout << "BuildDatabase: error with the number of arguments" << endl;
	}
	cout << "BuildDatabase: exit" << endl;
	return 0;
}

