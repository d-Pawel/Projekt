#include "encryption.hpp"


std::string binary::cast() {
	std::string r;
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

std::vector<std::string> binary::Split(const std::string & str, int splitLength)
{
	int NumSubstrings = str.length() / splitLength;
	std::vector<std::string> ret;

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

std::string binary::stringToBin(std::string text){
	std::string bintext= "";
	for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
		data = (int)*it;
		bintext += cast();
	}
	return bintext;
}

std::string binary::binToString(std::string bintext)
{
	std::string text = "";
	unsigned res,num;
	std::vector<std::string> letters = Split(bintext,8);
	for (int j = 0; j < letters.size(); j++)
	{
		num = std::atoi(letters[j].c_str());
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

binary::binary(std::string text) {
	stringToBin(text);
}

std::string & binary::operator=(std::string &r)
{
	return r;
}

std::ostream & operator <<(std::ostream &s, binary b) {
	return s << b.cast();
}

void encryption::generateKey(int length){
	key = "";
	for (int i = 0; i < length; i++){
		char ch = (char)(std::rand() % 95) + 32;
		key += ch;
	}	
}

encryption::encryption() {}

encryption::encryption(std::string filePath) throw(std::string) {
	encryption::filePath = filePath;
	encryption::file.open(filePath);
	if (!file.good()){
		std::string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

encryption::~encryption()
{
	file.close();
}

void encryption::encrypt(){
	std::ofstream cryptogramFile("cryptogram.txt");
	std::ofstream keyFile("key.txt");
	std::string text, binkey, temp = "";
	while (std::getline(file, temp)) //czyta plik
		text += temp + " ";


	generateKey(text.length()); //generuje klucz do zmiennej key klasy

	text = bn.stringToBin(text); //zamiana tekstu na kod binarny
	binkey = bn.stringToBin(key);

	for (int i = 0; i < text.length(); i++)	{ //szyfrowanie
		if (text.at(i) == binkey.at(i))
			cryptogram += '0';
		else cryptogram += '1';
	}

	cryptogramFile << cryptogram;
	keyFile << key;

	cryptogramFile.close();
	keyFile.close();
	std::cout << "Enryption complete";
}

void encryption::decrypt(std::string keyFilePath){
	std::string text, key, temp = "";
	std::ifstream keyFile;
	keyFile.open(keyFilePath);
	if (keyFile.good()){
		std::ofstream textFile("text.txt");
		while (std::getline(file, temp)) //czyta plik z tekstem zaszyfrowanym
			cryptogram += temp;
		while (std::getline(keyFile, temp)) //czyta plik z tekstem zaszyfrowanym
			key += temp;

		key = bn.stringToBin(key);

		for (int i = 0; i < cryptogram.length(); i++) { //szyfrowanie
			if (cryptogram.at(i) == key.at(i))
				text += '0';
			else text += '1';
		}

		text = bn.binToString(text);
		textFile << text;
		textFile.close();

		std::cout << "Decryption complete";
	}
	else{
		keyFile.close();
		std::string ex = "Blad otwarcia pliku!";
		throw ex;
	}
}

