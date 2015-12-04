#include "Encryption.hpp"
#include "Camera.hpp"
#include "ImageProcessing.hpp"
#include "FaceRecognition.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include <direct.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	srand(time(NULL));


	char plik_wejsciowy[20];
	char plik_haslo[20];


	encryption *en;
	Camera *cam;
	ImageProcessing *imgProcess;
	FaceRecognition *rec;

	int i = 1;

	while (i != 0) {


		cout << "1.Utworz uzytkownika\n2.Zaloguj sie\n";
		cin >> i;
		switch (i) {	
		case 1: {
			string user, faces;
			cout << "Podaj nazwe uzytkownika: ";
			cin >> user;
			string path = user;
			faces = "images/faces/" + user;
			user = "images/users/" + user;
			_mkdir(faces.c_str());
			_mkdir(user.c_str());
			cam = new Camera();
			cam->cameraCreateUser(path);
			break; }
		case 2: {
			_mkdir("images/temp");
			cam = new Camera();
			cam->cameraRecognizeUser();
			rec = new FaceRecognition();
			string login = rec->recognize();
						
			if (login != "NULL\n") {		//tymczasowe rozwiazanie ze stringiem
				int j;
				int logic = 0;
				while (logic == 0) {
					cout << "\n1.Szyfruj\n2.Deszyfruj\n3.Wyjdz\n";
					cin >> j;
					switch (j) {
					case 1:
						try
						{
							cout << "Podaj sciezke pliku do zaszyfrowania: ";
							cin >> plik_wejsciowy;
							string path = "files/" + login + "/" + plik_wejsciowy;
							en = new encryption(path,login);
							string cryptpath = "files/" + login + "/";
							en->encrypt(cryptpath);
							delete en;
						}
						catch (string ex)
						{
							cout << ex;
						}
						getchar();
						break;
					case 2:
						try {
							cout << "Podaj sciezke pliku do rozszyfrowania: ";
							cin >> plik_wejsciowy;
							//cout << "Podaj sciezke pliku z kluczem: ";
							//cin >> plik_haslo;
							string path = "files/" + login + "/";
							string pathcrypt = "files/" + login + "/" + plik_wejsciowy;
							//string pathkey = "files/" + login + "/" + plik_haslo;
							en = new encryption(pathcrypt, login);
							en->decrypt(path);
							delete en;
						}
						catch (string ex) {
							cout << ex;
						}
						getchar();
						break;
					case 3:
						logic = 1;
						break;
					}
				}

			}
		}
		/*case 6: {
			for (int i = 0; i < 3; i++) {
				string path = ("images/faces/Damian/"+to_string(i)+".jpg");		//kod do wycinania twarzy
				imgProcess = new ImageProcessing();								
				Mat temp = imread(path);
				imgProcess->saveFace(temp, path);
			}
			break;
		}*/
		default:
			break;
		}
	}



	getchar();
	return 0;
}