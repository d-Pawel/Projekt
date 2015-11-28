#ifndef IMAGEPROCESSING_HPP
#define IMAGEPROCESSING_HPP

#include <opencv2/opencv.hpp>

class ImageProcessing {
public:
	ImageProcessing();
	void saveFace(cv::Mat, std::string name);
	cv::Mat detectFace(cv::Mat frame);
private:
	std::string kaskadaDoRozpoznaniaTwarzy = "haarcascade_frontalface_alt.xml";
	cv::CascadeClassifier faceCascade;
};

#endif IMAGEPROCESSING_HPP