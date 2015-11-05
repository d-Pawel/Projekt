#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

string faceCascadeName = "haarcascade_frontalface_alt.xml";
CascadeClassifier faceCascade;

void detectFace(Mat img);

int main(int argc, char** argv)
{
	if (!faceCascade.load(faceCascadeName)) {        //£adowanie pliku ze sprawdzeniem poprawnoci 
		cout << "Nie znaleziono pliku " << faceCascadeName;
		return -2;
	}

	VideoCapture cap(0); // otwarcie domyslnej kamery oraz sprawdzenie
	if (!cap.isOpened())
	{
		cout << "Brak podlaczonej kamery"; return -1;
	}	

	for (;;)
	{
		vector<Rect> faces;
		Mat frame;		
		cap >> frame; // wczytanie klatki z kamery
		detectFace(frame);
		if (waitKey(30) >= 0) break;
	}

	// autoatyczne wylaczenie kamery w destruktorze
	return 0;
}

void detectFace(Mat frame) {
	vector<Rect> faces;                            //Utworzenie bufora na twarze 
	Mat greyFrame;                                //Utworzenie bufora na obrazek w odcieniach szarosci 
	Mat detectedFace;
	cvtColor(frame, greyFrame, CV_BGR2GRAY);                //Konwersja obrazu do odcieni szarosci 
	faceCascade.detectMultiScale(greyFrame, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(50, 50)); //wykrycie twarzy
	for (unsigned i = 0; i < faces.size(); i++) {
		Rect rectFace(faces[i]);    //Kwadrat okreslaj¹cy twarz ellipse( img, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 120, 12 ), 2, 2, 0 );							  
		rectangle(frame, rectFace, Scalar(120, 5, 86), 2, 2, 0); 
		detectedFace = greyFrame(faces[i]);
	}	
	imshow("Camera", frame);                         
}