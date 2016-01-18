#include "ImageProcessing.hpp"

using namespace std;
using namespace cv;	

	ImageProcessing::ImageProcessing()	{
		faceCascade.load(kaskadaDoRozpoznaniaTwarzy);
	}

	void ImageProcessing::saveFace(Mat frame, string name) {	
	vector<Rect> faces;	//Utworzenie bufora na twarze	
	Mat greyFrame;                                //Utworzenie bufora na obrazek w odcieniach szarosci 
	Mat detectedFace;
	cvtColor(frame, greyFrame, CV_BGR2GRAY);                //Konwersja obrazu do odcieni szarosci 
	faceCascade.detectMultiScale(greyFrame, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50)); //wykrycie twarzy
	for (unsigned i = 0; i < faces.size(); i++) {
		detectedFace = greyFrame(faces[i]);
	}
	if (faces.size() != NULL) {
		resize(detectedFace, detectedFace, Size(300, 300), 0, 0, CV_INTER_CUBIC);		
		imwrite(name, detectedFace);
	}
	else {
		imwrite(name, frame);
	}
	
}


Mat ImageProcessing::detectFace(Mat frame) {	
	vector<Rect> faces;                            //Utworzenie bufora na twarze 
	Mat greyFrame;                                 //Utworzenie bufora na obrazek w odcieniach szarosci 
	cvtColor(frame, greyFrame, CV_BGR2GRAY);                //Konwersja obrazu do odcieni szarosci 
	faceCascade.detectMultiScale(greyFrame, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50)); //wykrycie twarzy
	for (unsigned i = 0; i < faces.size(); i++) {
		Rect rectFace(faces[i]);    //Kwadrat okreslaj¹cy twarz							  
		rectangle(frame, rectFace, Scalar(120, 5, 86), 2, 2, 0);
	}
	return frame;
}