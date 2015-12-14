#ifndef Encryption_hpp
#define Encryption_hpp

#include "Binary.hpp"
#include <string>
#include <fstream>
#include <vector>



class encryption {
private:
	binary bn = binary();
	//const int keyLength = 100;
	int keyLength = 0;
	std::ifstream file;
	std::string filePath;
	std::string fileName;
	std::string fileExtension;
	std::string userLogin;
	std::string key;
	std::string cryptogram = "";
	void generateKey(int length);
	void generateKeyByLogin();
public:
	encryption();
	encryption(std::string filePath) throw(std::string);
	encryption(std::string filePath, std::string userLogin) throw(std::string);
	~encryption();
	void encrypt(std::string path);
	void decrypt(std::string path);	
};

#endif
