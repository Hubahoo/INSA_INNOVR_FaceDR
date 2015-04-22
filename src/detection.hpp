#ifndef DETECTION_HPP
#define DETECTION_HPP

#include <vector>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int detectFaces(cv::Mat frame, cv::CascadeClassifier faceCascade, std::vector<cv::Mat> &faces);

#endif //DETECTION_HPP

