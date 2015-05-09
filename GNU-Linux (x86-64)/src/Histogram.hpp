#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "define.hpp"

class Histogram
{
public:
	Histogram();
	Histogram(cv::Mat image);
	~Histogram();

	Histogram& operator=(Histogram const& h);

	void saveHistogram(std::string filename);
	float distance(Histogram h);
	std::string toString();
	
	
private:
	friend class boost::serialization::access;
	
	int tab[NB_OF_REGIONS][256];
	unsigned char computeLBP(cv::Mat image, int x, int y);
	
	template<class Archive>
	void serialize (Archive & ar, const unsigned int version) {
		ar & tab;
	}

};




#endif //HISTOGRAM.HPP


