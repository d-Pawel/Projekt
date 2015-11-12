#ifndef Binary_hpp
#define Binary_hpp

#include <string>
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

#endif