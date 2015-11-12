#include "Binary.hpp"
#include <iostream>

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

string binary::stringToBin(string text) {
	string bintext = "";
	for (string::iterator it = text.begin(); it != text.end(); ++it) {
		data = (int)*it;
		bintext += cast();
	}
	return bintext;
}

string binary::binToString(string bintext)
{
	string text = "";
	unsigned res, num;
	vector<string> letters = Split(bintext, 8);
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