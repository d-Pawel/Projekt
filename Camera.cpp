#include "Camera.hpp"
#include <opencv2/opencv.hpp>
#include "ImageProcessing.hpp"

using namespace std;
using namespace cv;

void Camera::cameraCreateUser(string path) {
	VideoCapture cap(0);
	int i = 0;
	ImageProcessing *imgProcess;
	imgProcess = new ImageProcessing();

	for (;;) {
		vector<Rect> faces;
		Mat frame;
		int key;
		cap >> frame; // wczytanie klatki z kamery

		if ((key = waitKey(30)) >= 0) {
			string s = to_string(i);
			string name = "images/faces/"+path+"/"+ s + ".jpg";
			if (key == 13) {			//zapisanie zdjecia po wcisnieciu Enter
				imwrite(name, frame);
				i++;
			}
			if (key == 27) break;					//zamkniecie kamery po wcisnieciu Escape
		}
		frame = imgProcess->detectFace(frame);
		imshow("Camera", frame);
	}
	destroyWindow("Camera");
}

void Camera::cameraRecognizeUser() {
	VideoCapture cap(0);
	ImageProcessing *imgProcess;
	imgProcess = new ImageProcessing();
	for (;;) {
		Mat frame;
		int key;
		cap >> frame; // wczytanie klatki z kamery

		if ((key = waitKey(30)) >= 0) {			
			string name = "images/temp/temp.jpg";
			imwrite(name, frame);
			break;					//zamkniecie kamery po wcisnieciu Escape
		}
		frame = imgProcess->detectFace(frame);
		imshow("Camera", frame);
	}
	destroyWindow("Camera");
}
