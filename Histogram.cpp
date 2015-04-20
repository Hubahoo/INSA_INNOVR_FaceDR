#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Histogram.hpp"

// Initialization of constants
const int Histogram::P = 8;
const int Histogram::R = 2;

const int Histogram::K = 1;
const int Histogram::NB_OF_REGIONS = K*K;
const int Histogram::REGION_WIDTH = 130;//26
const int Histogram::REGION_HEIGHT = 150;//30

Histogram::Histogram()
{
	for (int i = 0 ; i < NB_OF_REGIONS ; i++){
		for (int j = 0 ; j < 256 ; j++){
			this->tab[i][j] = 0;
		}
	}
}

Histogram::Histogram(cv::Mat image)
{	
	int height = image.rows;
	int width = image.cols;
	unsigned char lbp = 0;
	unsigned char region = 0;

	for (int i = 0 ;  i < NB_OF_REGIONS ; i++){
		for (int j = 0 ; j < 256 ; j++){
			this->tab[i][j] = 0;
		}
	}
	
	std::cout << "FaceRecognition: computing Local Binary Patterns ..." << std::endl;
	
	for (int i = R ; i < width - R ; i++){
		for(int j = R ; j < height - R ; j++){
		
			lbp = computeLBP(image, i, j);
			
			// Select the correct region
			region = K*((int)(i/REGION_WIDTH)) + (int)(j/REGION_HEIGHT);
			this->tab[region][lbp]++;
		}
	}
}


Histogram::~Histogram()
{
}

Histogram& Histogram::operator=(Histogram const& h)
{
	if (this != &h){
		for (int i = 0 ; i < NB_OF_REGIONS ; i++){
			for (int j = 0 ; j < 256 ; j++){
				this->tab[i][j] = h.tab[i][j];
			}
		}
	}
	return *this;
}

void Histogram::saveHistogram(std::string filename)
{
	std::ofstream file(filename.c_str(), std::ios::out);

	if(file){
		for(int i = 0 ; i < NB_OF_REGIONS ; i++){
			file << "region " << i << " ; ";

			for(int j = 0 ; j < 256 ; j++){
				file << tab[i][j] << " ; ";
			}
			file << std::endl;
		}

		file.close();
	}
	else{
		std::cout << "Error: can't save the histogram" << std::endl;
	}
}


float Histogram::distance(Histogram h)
{
	float distance = 0;
	int a = 0;
	int b = 0;

	for (int i = 0 ; i < NB_OF_REGIONS ; i++){
		for(int j = 0 ; j < 256 ; j++){
			a = h.tab[i][j];
			b = this->tab[i][j];
			
			if(a + b != 0){
				distance += ((float)(a - b)*(a - b))/(a + b);
			}
		}
	}

	return distance;
}

std::string Histogram::toString()
{
	std::stringstream ss;
	
	for (int i = 0 ; i < NB_OF_REGIONS ; i++){
		for(int j = 0 ; j < 256 ; j++){
			ss << tab[i][j] << ",";
		}
		ss << ";";
	}
	
	return ss.str();
}

unsigned char Histogram::computeLBP(cv::Mat image, int x, int y)
{
	//compute the LBP(8,2)
	
	unsigned char lbp = 0;
	unsigned char center = image.at<uchar>(y, x);
	unsigned char tmp = 0;

	tmp = image.at<uchar>(y, x + 2);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y + 1, x + 1);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y + 2, x);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y + 1, x - 1);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y, x - 2);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y - 1, x - 1);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y - 2, x);
	if(tmp > center){
		lbp++;
	}
	lbp = lbp << 1;

	tmp = image.at<uchar>(y - 1, x + 1);
	if(tmp > center){
		lbp++;
	}

	return lbp;
}


