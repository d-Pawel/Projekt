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
			string name = "images/users/"+path+"/"+ s + ".jpg";
			if (key == 13) {			//zapisanie zdjecia po wcisnieciu Enter
				imwrite(name, frame);
				i++;
				string name = "images/faces/" + path + "/" + s + ".jpg";
				imgProcess->saveFace(frame, name);
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
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	ImageProcessing *imgProcess;
	imgProcess = new ImageProcessing();
	for (;;) {
		Mat frame;
		int key;
		cap >> frame; // wczytanie klatki z kamery
		if ((key = waitKey(30)) >= 0) {
			string name = "images/temp/temp.jpg";
			if (key == 13) {			//zapisanie zdjecia po wcisnieciu Enter
				imgProcess->saveFace(frame, name);
				break;
			}
			if (key == 27) break;					//zamkniecie kamery po wcisnieciu Escape
		}
		frame = imgProcess->detectFace(frame);
		imshow("Camera", frame);
	}
	destroyWindow("Camera");
}
