/*
* Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
* Released to public domain under terms of the BSD Simplified license.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of the organization nor the names of its contributors
*     may be used to endorse or promote products derived from this software
*     without specific prior written permission.
*
*   See <http://www.opensource.org/licenses/bsd-license>
*/

#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, vector<string>& names, char separator = ';') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message = "No valid input file was given, please check the given filename.";
		CV_Error(CV_StsBadArg, error_message);
	}
	string line, path, classlabel, classnames;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel, separator);
		getline(liness, classnames);
		if (!path.empty() && !classlabel.empty() && !classnames.empty()) {
			images.push_back(imread(path, 0));
			labels.push_back(atoi(classlabel.c_str()));
			names.push_back(classnames.c_str());
		}
	}
}

int main(int argc, const char *argv[]) {

	string fn_csv = string("D:\\STUDIA\\projekt nowy\\Projekt\\faces.csv"); // ustawic uniwersalna sciezke!!!!!!!!
	vector<Mat> images;
	vector<int> labels;
	vector<string> names;
	
	try {
		read_csv(fn_csv, images, labels, names);
	}
	//lapanie bledu otwarcia pliku CSV
	catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
		system("PAUSE");
		exit(1);
	}

	//sprawdzenie ilosci zdjec
	if (images.size() <= 1) { 
		string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(CV_StsError, error_message);
	}
	
	//zdjecie do rozpoznawania
	Mat testSample = imread("D:\\STUDIA\\projekt nowy\\Projekt\\images\\test\\0.jpg", 0); //sciezka !!!!!!!!!

	//trenowanie algorytmu
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	model->train(images, labels);

	//proba rozpoznania
	int predictedLabel = model->predict(testSample);
	cout << "Predicted class = " << predictedLabel << endl;
	int i = 0;
	while (labels[i] != predictedLabel) i++;
	cout << "Witaj, " << names[i] << "!" << endl;

	system("PAUSE");
	return 0;
}
