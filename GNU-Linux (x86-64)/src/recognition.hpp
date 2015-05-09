#ifndef RECOGNITION_HPP
#define RECOGNITION_HPP

#include <vector>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "Gallery.hpp"

/**
 * Search in the gallery the faces.
 */
int recognitionFaces(Gallery g, std::vector<cv::Mat> faces);

#endif // RECOGNITION_HPP

