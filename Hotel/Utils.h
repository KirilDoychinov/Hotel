#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils
{
	bool isDigit(char);
	bool isNaturalNumber(const std::string&);
	bool isDate(const std::string&);
	bool isLeapYear(int);
	void trim(std::string&);	
};

#endif

