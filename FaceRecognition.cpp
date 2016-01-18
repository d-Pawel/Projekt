#include "FaceRecognition.hpp"
#define staticPredictedConfidence 72.0 // prog dokladnosci rozpoznawania twarzy.


using namespace cv;
using namespace cv::face;
using namespace std;

string FaceRecognition::recognize() {
	string fn_csv = string("faces.csv"); 
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
	Mat testSample = imread("images/temp/temp.jpg", 0); 

	//trenowanie algorytmu
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer(1,8,12,12,DBL_MAX);
	model->train(images, labels);

	//proba rozpoznania
	int predictedLabel = -1;
	double predictedConfidence = 0.0;
	model->predict(testSample, predictedLabel, predictedConfidence);
	cout << "Predicted confidence = " << predictedConfidence << endl;

	
	if (predictedConfidence > staticPredictedConfidence) {
		predictedLabel = -1;
		cout << "Nie rozpoznano uzytkownika." << endl;		
		return "NULL";
	}
	else {
		int nameIndex = 0;
		while (labels[nameIndex] != predictedLabel) nameIndex++;
		cout << "Witaj, " << names[nameIndex] << "!" << endl;
		return names[nameIndex];

	}	
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
