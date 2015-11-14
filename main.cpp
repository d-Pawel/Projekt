#include "encryption.hpp"
#include "Camera.hpp"
#include "ImageProcessing.hpp"
#include "FaceRecognition.hpp"
#include <iostream>
#include <ctime>
#include <direct.h>

using namespace std;


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


		cout << "1.Szyfruj\n2.Deszyfruj\n3.Zapisz twarz\n4.Utworz uzytkownika\n5.Rozpoznaj uzytkownika\n";
		cin >> i;
		switch (i)
		{
		case 1:
			try
			{
				cout << "Podaj sciezke pliku do zaszyfrowania: ";
				cin >> plik_wejsciowy;
				en = new encryption(plik_wejsciowy);
				en->encrypt();
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
				cout << "Podaj sciezke pliku z kluczem: ";
				cin >> plik_haslo;
				en = new encryption(plik_wejsciowy);
				en->decrypt(plik_haslo);
				delete en;
			}
			catch (string ex) {
				cout << ex;
			}
			getchar();
			break;
		case 3:
			imgProcess = new ImageProcessing();
			imgProcess->saveFace("images/0.jpg","twarz.jpg");
			break;
		case 4: {
			string user;
			cout << "Podaj nazwe uzytkownika: ";
			cin >> user;
			string path = user;
			user = "images/faces/" + user;
			_mkdir(user.c_str());
			cam = new Camera();
			cam->cameraCreateUser(path);
			break; }
		case 5:
			_mkdir("images/temp");
			cam = new Camera();
			cam->cameraRecognizeUser();
			rec = new FaceRecognition();
			rec->recognize();
			break;

		default:
			break;
		}
	}



	getchar();
	return 0;
}