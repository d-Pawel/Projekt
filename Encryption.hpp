#ifndef Encryption_hpp
#define Encryption_hpp

#include "binary.hpp"
#include <string>
#include <fstream>
#include <vector>



class encryption {
private:
	binary bn = binary();
	const int keyLength = 100;
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
