#ifndef TEXT_UTILITIES_H
#define TEXT_UTILITIES_H

#include "Date.h"
#include <string>
#include <vector>

/**
 * @namespace	TextUtilities
 *
 * @brief		Contains some useful methods for manipulation of string-based data
 */

namespace TextUtilities
{
	void trim(std::string& str);
	Date* extractDate(const std::string& str);
	void removeFirstAndLastElement(std::string& str);
	std::vector<std::string> extractTokens(const std::string& str);
};

#endif

