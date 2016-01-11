#include "Encryption.hpp"
#include <iostream>
#include <sstream>

using namespace std;



void encryption::generateKey(int length){
	key = "";
	for (int i = 0; i < length; i++){
		char ch = (char)(rand() % 95) + 32;
		key += ch;
	}	
}

void encryption::generateKeyByLogin() {
	key = "";
	int loginLen = userLogin.length();
	encryption::keyLength = loginLen;
	key = userLogin;
	/*int* letters = new int[loginLen];
	for (unsigned i = 0; i < loginLen; ++i)
	{
	letters[i] = (int)userLogin.at(i) * loginLen;
	}*/
}

encryption::encryption() {}

encryption::encryption(string filePath) throw(string) {
	encryption::filePath = filePath;
	encryption::file.open(filePath, std::ios_base::binary);
	if (!file.good()){
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

encryption::encryption(std::string filePath, std::string userLogin) throw(std::string)
{
	encryption::userLogin = userLogin;
	encryption::filePath = filePath;
	encryption::fileName = filePath.replace(0, filePath.find_last_of("/") + 1, "");
	encryption::fileName.replace(filePath.find_last_of("."), encryption::fileName.length(), "");
	encryption::fileExtension = encryption::filePath.substr(encryption::filePath.find_last_of(".") + 1);

	encryption::file.open(encryption::filePath, std::ios_base::binary);
	if (!file.good()) {
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

encryption::~encryption()
{
	file.close();
}

void encryption::encrypt(string path){
	ofstream cryptogramFile((path + userLogin + "_" + fileName + "_" + fileExtension + ".bin"), std::ios::binary);
	//ofstream keyFile((path+"key.bin"), std::ios::binary);
	string text, binkey, temp = "";

	size_t found = filePath.find_last_of(".");
	string extension = filePath.substr(found + 1);

	vector<char> buffer((
		istreambuf_iterator<char>(file)),
		(istreambuf_iterator<char>()));

	if (!buffer.empty()){
		string str(buffer.begin(), buffer.end());
		str = fileName + "\r\n" + userLogin + "\r\n" + extension + "\r\n" + str;
		//generateKey(keyLength); 
		generateKeyByLogin();
		text = bn.stringToBin(str); 
		binkey = bn.stringToBin(key);

		
		for (int i = 0; i < text.length(); i++) { 
			if (text.at(i) == binkey.at(i%keyLength))
				cryptogram += '0';
			else cryptogram += '1';
		}

		cryptogram = bn.binToString(cryptogram);
		copy(cryptogram.begin(), cryptogram.end(), ostreambuf_iterator<char>(cryptogramFile));
		//copy(key.begin(), key.end(), ostreambuf_iterator<char>(keyFile));

		cout << "Enryption complete" << endl;
	}
	else {
		cout << "File is empty" << endl;
	}
	
	cryptogramFile.close();
	//keyFile.close();

}

void encryption::decrypt(string path){
	string text, tempkey, temp = "";
	//ifstream keyFile;
	/*keyFile.open(keyFilePath, std::ios_base::binary);
	if (keyFile.good()){*/
		

		vector<char> buffer((
			istreambuf_iterator<char>(file)),
			(istreambuf_iterator<char>()));

		if (!buffer.empty()) {
			string str(buffer.begin(), buffer.end());

			/*vector<char> bufferkey((
				istreambuf_iterator<char>(keyFile)),
				(istreambuf_iterator<char>()));

			string key(bufferkey.begin(), bufferkey.end());*/

			generateKeyByLogin();
			cryptogram = str;
			tempkey = bn.stringToBin(key);
			cryptogram = bn.stringToBin(cryptogram);

			for (int i = 0; i < cryptogram.length(); i++) { //szyfrowanie
				if (cryptogram.at(i) == tempkey.at(i%keyLength))
					text += '0';
				else text += '1';
			}

			text = bn.binToString(text);
			istringstream f(text);
			string realfilename;
			string caption;
			string extension;
			getline(f, realfilename);
			getline(f, caption);
			getline(f, extension);

			text.replace(0, realfilename.find_last_of("\r") + 2, "");
			text.replace(0, caption.find_last_of("\r") + 2, "");
			text.replace(0, extension.find_last_of("\r") + 2, "");
			realfilename.replace(realfilename.find_last_of("\r"), 2, "");
			extension.replace(extension.find_last_of("\r"), 2, "");
			caption.replace(caption.find_last_of("\r"), 2, "");
			
			if (userLogin == caption)
			{
				ofstream textFile(path + realfilename + "." + extension, std::ios_base::binary);
				std::copy(text.begin(), text.end(), std::ostreambuf_iterator<char>(textFile));
				textFile.close();

				cout << "Decryption complete" << endl;
				textFile.close();
			}
			else
			{
				string ex = "Error: wrong file user";
				throw ex;
			}

			
		/*}
		else {
			cout << "File is empty" << endl;
		}*/
		
		//keyFile.close();
		
	}
	else{
		//keyFile.close();
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

