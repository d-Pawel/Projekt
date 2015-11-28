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

encryption::encryption() {}

encryption::encryption(string filePath) throw(string) {
	encryption::filePath = filePath;
	encryption::file.open(filePath, std::ios_base::binary);
	if (!file.good()){
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

encryption::~encryption()
{
	file.close();
}

void encryption::encrypt(string path){
	ofstream cryptogramFile((path+"cryptogram.bin"), std::ios::binary);
	ofstream keyFile((path+"key.bin"), std::ios::binary);
	string text, binkey, temp = "";

	size_t found = filePath.find_last_of(".");
	string extension = filePath.substr(found + 1);

	vector<char> buffer((
		istreambuf_iterator<char>(file)),
		(istreambuf_iterator<char>()));

	if (!buffer.empty()){
		string str(buffer.begin(), buffer.end());
		str = extension + "\r\n" + str;
		generateKey(keyLength); 
		text = bn.stringToBin(str); 
		binkey = bn.stringToBin(key);

		
		for (int i = 0; i < text.length(); i++) { 
			if (text.at(i) == binkey.at(i%keyLength))
				cryptogram += '0';
			else cryptogram += '1';
		}

		cryptogram = bn.binToString(cryptogram);
		copy(cryptogram.begin(), cryptogram.end(), ostreambuf_iterator<char>(cryptogramFile));
		copy(key.begin(), key.end(), ostreambuf_iterator<char>(keyFile));

		cout << "Enryption complete" << endl;
	}
	else {
		cout << "File is empty" << endl;
	}
	
	cryptogramFile.close();
	keyFile.close();

}

void encryption::decrypt(string keyFilePath, string path){
	string text, key, temp = "";
	ifstream keyFile;
	keyFile.open(keyFilePath, std::ios_base::binary);
	if (keyFile.good()){
		

		vector<char> buffer((
			istreambuf_iterator<char>(file)),
			(istreambuf_iterator<char>()));

		if (!buffer.empty()) {
			string str(buffer.begin(), buffer.end());

			vector<char> bufferkey((
				istreambuf_iterator<char>(keyFile)),
				(istreambuf_iterator<char>()));

			string key(bufferkey.begin(), bufferkey.end());

			cryptogram = str;
			key = bn.stringToBin(key);
			cryptogram = bn.stringToBin(cryptogram);

			for (int i = 0; i < cryptogram.length(); i++) { //szyfrowanie
				if (cryptogram.at(i) == key.at(i%keyLength))
					text += '0';
				else text += '1';
			}

			text = bn.binToString(text);
			istringstream f(text);
			string extension;
			getline(f, extension);

			text.replace(0, extension.find_last_of("\r") + 2, "");
			extension.replace(extension.find_last_of("\r"), 2, "");
			
			ofstream textFile(path + "plik2." + extension, std::ios_base::binary);
			std::copy(text.begin(), text.end(), std::ostreambuf_iterator<char>(textFile));
			textFile.close();

			cout << "Decryption complete" << endl;
			textFile.close();
		}
		else {
			cout << "File is empty" << endl;
		}
		
		keyFile.close();
		
	}
	else{
		keyFile.close();
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

