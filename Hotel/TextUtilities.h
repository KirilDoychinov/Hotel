#ifndef TEXT_UTILITIES_H
#define TEXT_UTILITIES_H

#include "Date.h"
#include <string>
#include <vector>

namespace TextUtilities
{
	void trim(std::string& str);
	Date* extractDate(const std::string& str);
	void extractContent(std::string& str);
	std::vector<std::string> extractTokens(const std::string& str, char delimeter = ' ');
};

#endif

