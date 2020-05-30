#include "TextUtilities.h"
#include <cassert>

/**
 * @brief				 Trims in-place the given string removing all leading and trailing whitespace characters.
 * 						 Whitespace characters are denoted by isspace() standart function and include
 *						 space, form feed, line feed, carriage return, horizontal tab and vertical tab
 *
 * @param [in,out]	str	 String to be trimmed
 *
 */

void TextUtilities::trim(std::string& str) {
	if (str.empty())
		return;

	std::string spaceCharacters = " \t\f\v\n\r";

	std::size_t start = str.find_first_not_of(spaceCharacters);
	std::size_t end = str.std::string::find_last_not_of(spaceCharacters);

	if (start != std::string::npos)
		str = str.substr(start, end - start + 1);
}

/**
 * @brief		Extracts a date object from a given zero-terminated string that MUST be in
 *				format YYYY-MM-DD (ISO 8601).
 *
 * @param [in]	str	the string that represents the date in  yyyy-mm-dd format.
 *
 * @returns		Date representing the given date string
 *
 * @throws		std::invalid_argument exception if string is not in the given format, or assertion error
 * 				if the string is not of the required size of 10.
 */

Date* TextUtilities::extractDate(const std::string& str) {
	assert(str.size() == 10);

	int year = std::stoi(str.substr(0, 4));
	int month = std::stoi(str.substr(5, 2));
	int day = std::stoi(str.substr(8, 2));

	return new Date(day, month, year);
}

/**
 * @brief				  Removes in-place the first and last element of given non-empty string
 *
 * @param [in,out]  str   String to be manipulated
 *
 * @throws				  Assertion error if the given string is empty
 *
 */

void TextUtilities::removeFirstAndLastElement(std::string& str) {
	str.erase(0, 1);

	if (!str.empty())
		str.pop_back();
}

/**
 * @brief						Extracts word tokens from a given string treating space character as a
 * 								delimeter. Space is being escaped only if enclosed by curly brackets -
 * 								'{' '}' or quotation marks - '"'
 *
 * @param [in]  str				String to be extracted from
 *
 * @returns						list of extracted string tokens
 */

std::vector<std::string> TextUtilities::extractTokens(const std::string& str) {
	std::vector<std::string> tokens;

	bool quotes = false, brackets = false;
	size_t start = 0;

	for (size_t i = 0; i < str.size(); ++i) {
		char ch = str.at(i);

		if (i == str.size() - 1)
			tokens.push_back(str.substr(start, i - start + 1));

		else if (ch == '{')
			brackets = true;

		else if (ch == '}')
			brackets = false;

		else if (ch == '"')
			quotes = not quotes;

		else if (ch == ' ' && !quotes && !brackets) {
			tokens.push_back(str.substr(start, i - start));
			start = i + 1;
		}
	}

	return tokens;
}
