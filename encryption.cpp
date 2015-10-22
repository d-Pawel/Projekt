#include "encryption.hpp"

using namespace std;

string binary::cast() {
	string r;
	char lead = 0;
	for (int mask = 1 << 7; mask != 0; mask >>= 1) {
		if ((data & mask)) {
			//lead = 1;
			r += "1";
		}
		else {//if (lead) {
			r += "0";
		}
		//if (mask&((1 << 4) | (1 << 8) | (1 << 12)) && lead) r += " ";
	}
	return r;
}

vector<string> binary::Split(const string & str, int splitLength)
{
	int NumSubstrings = str.length() / splitLength;
	vector<string> ret;

	for (auto i = 0; i < NumSubstrings; i++)
	{
		ret.push_back(str.substr(i * splitLength, splitLength));
	}

	// If there are leftover characters, create a shorter item at the end.
	if (str.length() % splitLength != 0)
	{
		ret.push_back(str.substr(splitLength * NumSubstrings));
	}

	return ret;
}

string binary::stringToBin(string text){
	string bintext= "";
	for (string::iterator it = text.begin(); it != text.end(); ++it) {
		data = (int)*it;
		bintext += cast();
	}
	return bintext;
}

string binary::binToString(string bintext)
{
	string text = "";
	unsigned res,num;
	vector<string> letters = Split(bintext,8);
	for (int j = 0; j < letters.size(); j++)
	{
		num = atoi(letters[j].c_str());
		res = 0;
		for (int i = 0; num > 0; ++i)
		{
			if ((num % 10) == 1)
				res += (1 << i);

			num /= 10;
		}
		text += (char)res;
	}
		
	return text;
}

binary::binary() :data(0) {}

binary::binary(int l) {
	data = l;
	cast();
}

binary::binary(string text) {
	stringToBin(text);
}

string & binary::operator=(string &r)
{
	return r;
}

ostream & operator <<(ostream &s, binary b) {
	return s << b.cast();
}

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
	encryption::file.open(filePath);
	if (!file.good()){
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

encryption::~encryption()
{
	file.close();
}

void encryption::encrypt(){
	ofstream cryptogramFile("cryptogram.txt");
	ofstream keyFile("key.txt");
	string text, binkey, temp = "";
	while (getline(file, temp)) //czyta plik
		text += temp + " ";


	generateKey(text.length()); //generuje klucz do zmiennej key klasy

	text = bn.stringToBin(text); //zamiana tekstu na kod binarny
	binkey = bn.stringToBin(key);

	for (int i = 0; i < text.length(); i++)	{ //szyfrowanie
		if (text.at(i) == binkey.at(i))
			cryptogram += '0';
		else cryptogram += '1';
	}

	cryptogram = bn.binToString(cryptogram);
	cryptogramFile << cryptogram;
	keyFile << key;

	cryptogramFile.close();
	keyFile.close();
	cout << "Enryption complete";
}

void encryption::decrypt(string keyFilePath){
	string text, key, temp = "";
	ifstream keyFile;
	keyFile.open(keyFilePath);
	if (keyFile.good()){
		ofstream textFile("text.txt");
		while (getline(file, temp)) //czyta plik z tekstem zaszyfrowanym
			cryptogram += temp;
		while (getline(keyFile, temp)) //czyta plik z tekstem zaszyfrowanym
			key += temp;

		key = bn.stringToBin(key);
		cryptogram = bn.stringToBin(cryptogram);

		for (int i = 0; i < cryptogram.length(); i++) { //szyfrowanie
			if (cryptogram.at(i) == key.at(i))
				text += '0';
			else text += '1';
		}

		text = bn.binToString(text);
		textFile << text;
		textFile.close();

		cout << "Decryption complete";
	}
	else{
		keyFile.close();
		string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

