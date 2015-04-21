#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <opencv2/opencv.hpp>

class Histogram
{
public:
	Histogram();
	Histogram(cv::Mat image);
	~Histogram();

	Histogram& operator=(Histogram const& h);

	// Declaration of constants
	static const int P;
	static const int R;

	static const int K;
	static const int NB_OF_REGIONS;
	static const int REGION_WIDTH;
	static const int REGION_HEIGHT;

	void saveHistogram(std::string filename);
	float distance(Histogram h);
	std::string toString();
	
	
private:
	friend class boost::serialization::access;
	
	int tab[1][256];// à changer
	unsigned char computeLBP(cv::Mat image, int x, int y);
	
	template<class Archive>
	void serialize (Archive & ar, const unsigned int version) {
		ar & tab;
	}

};




#endif //HISTOGRAM.HPP


