#ifndef encryption_hpp
#define encryption_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

class binary {
	unsigned short data;
	std::string cast();
	std::vector<std::string> Split(const std::string& str, int splitLength);
public:
	binary();
	binary(int);
	binary(std::string text);
	std::string stringToBin(std::string text);
	std::string binToString(std::string bintext);
	//template <class T> binary(const T& d) : data(d) {}
	friend std::ostream & operator <<(std::ostream &, binary);
	std::string & binary::operator =(std::string&);
};

class encryption {
private:
	binary bn = binary();
	const int keyLength = 10;
	std::ifstream file;
	std::string filePath;
	std::string key;
	std::string cryptogram = "";
	void generateKey(int length);
public:
	encryption();
	encryption(std::string filePath) throw(std::string);
	~encryption();
	void encrypt();
	void decrypt(std::string keyFilePath);

};

#endif
