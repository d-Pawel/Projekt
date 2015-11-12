#include "FaceRecognition.hpp"

using namespace cv;
using namespace cv::face;
using namespace std;

void FaceRecognition::recognize() {
	string fn_csv = string("faces.csv"); // ustawic uniwersalna sciezke!!!!!!!!
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
	Mat testSample = imread("images/temp/temp.jpg", 0); //sciezka !!!!!!!!!

																						  //trenowanie algorytmu
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	model->train(images, labels);

	//proba rozpoznania
	int predictedLabel = model->predict(testSample);
	cout << "Predicted class = " << predictedLabel << endl;
	int i = 0;
	while (labels[i] != predictedLabel) i++;
	cout << "Witaj, " << names[i] << "!" << endl;
}

void FaceRecognition::read_csv(const std::string & filename, std::vector<cv::Mat>& images, std::vector<int>& labels, std::vector<std::string>& names, char separator) {
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
