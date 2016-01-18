#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QFileDialog>
#include "Encryption.hpp"
#include "Camera.hpp"
#include "ImageProcessing.hpp"
#include "FaceRecognition.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include <direct.h>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QInputDialog>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
	
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_szyfruj_clicked()
{
	bool ok;
	encryption *en;
	//QString fileName;
	string path, test;
    QString fileName = QFileDialog::getOpenFileName (
               this,
               tr("Open File"),
               "examples/",			   
               "All files(*.*)"
               );
	test = fileName.toStdString();
	if (test.empty()) { return; }
	/*fileName = QInputDialog::getText(this, tr("QInputDialog::getText()"),
				tr("User name:"), QLineEdit::Normal,
				QDir::home().dirName(), &ok);*/
   try
   {
	   path = fileName.toStdString();
	   //path = ("files/"+ login + "/" + path);
	   cout << path;
	   en = new encryption(path, login);
	   //string cryptpath = path.substr(0, path.find_last_of('/')+1);
	   path = ("files/" + login + "/");
	   en->encrypt(path);
	   delete en;
   }
   catch (string ex)
   {
	   cout << ex;
   }
   return;
}

void MainWindow::on_deszyfruj_clicked()
{
	bool ok;
	string path;
	encryption *en;
    QString fileName = QFileDialog::getOpenFileName (
                this,
                tr("Open File"),
				("files/" + QString::fromStdString(login)),
                "All files(*.bin)"
				);
	if (fileName.toStdString().empty()) { return; }

	cout << fileName.toStdString();

	try {
		string pathcrypt = fileName.toStdString();	
		path = fileName.toStdString();
		en = new encryption(path,login);
		path = ("files/" + login + "/");
		en->decrypt(path);
		delete en;
	}
	catch (string ex) {
		cout << ex;
	}
	return;
}

void MainWindow::on_dodajUzytkownika_clicked()
{
	bool ok;
	Camera *cam;
	QString nazwaNowegoUzytkownika;
	QString test;
	string faces;
	string user;
	nazwaNowegoUzytkownika = QInputDialog::getText(this, tr("Dodaj uzytkownika:"),
		tr("Login:"), QLineEdit::Normal,
		QDir::home().dirName(), &ok);
	if (ok && !nazwaNowegoUzytkownika.isEmpty()) {

		user = nazwaNowegoUzytkownika.toStdString();
		string path = user;
		faces = "images/faces/" + user;
		string files = "files/" + user;
		user = "images/users/" + user;
		
		_mkdir(faces.c_str());
		_mkdir(user.c_str());
		_mkdir(files.c_str());
		cam = new Camera();
		cam->cameraCreateUser(path);
	}
}

void MainWindow::on_rozpoznajTwarz_clicked()
{
	Camera *cam;
	ImageProcessing *imgProcess;
	FaceRecognition *rec;
	_mkdir("images/temp");
	cam = new Camera();
	cam->cameraRecognizeUser();
	rec = new FaceRecognition();

	login = rec->recognize();
	if (login == "NULL") {
		QString komunikat = "Nie rozpoznano uzytkownika";
		ui->nazwaUzytkownika->setText(komunikat);
		komunikat = "";
	}
	else {
		QString komunikat = QString::fromStdString("Witaj "+login);
		ui->nazwaUzytkownika->setText(komunikat);
		ui->szyfruj->setEnabled(true);
		ui->deszyfruj->setEnabled(true);
		ui->wyloguj->setEnabled(true);
		ui->dodajUzytkownika->setEnabled(false);
		ui->rozpoznajTwarz->setEnabled(false);
		komunikat = "";
	}
}
void MainWindow::on_wyloguj_clicked()
{
	ui->szyfruj->setEnabled(false);
	ui->deszyfruj->setEnabled(false);
	ui->dodajUzytkownika->setEnabled(true);
	ui->rozpoznajTwarz->setEnabled(true);
	ui->wyloguj->setEnabled(false);
	ui->nazwaUzytkownika->setText("Zaloguj sie lub utworz swoje konto");
}

