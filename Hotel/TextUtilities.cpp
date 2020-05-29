#include "TextUtilities.h"

void TextUtilities::trim(std::string& str) {
	if (str.empty())
		return;

	std::string spaceCharacters = " \t\f\v\n\r";

	std::size_t start = str.find_first_not_of(spaceCharacters);
	std::size_t end = str.std::string::find_last_not_of(spaceCharacters);

	if (start != std::string::npos)
		str = str.substr(start, end - start + 1);
}

Date* TextUtilities::extractDate(const std::string& str) {
	int year = std::stoi(str.substr(0, 4));
	int month = std::stoi(str.substr(5, 2));
	int day = std::stoi(str.substr(8, 2));

	return new Date(day, month, year);
}

void TextUtilities::extractContent(std::string& str) {
	str.erase(0, 1);
	str.pop_back();
}

std::vector<std::string> TextUtilities::extractTokens(const std::string& line, char delimeter) {
	std::vector<std::string> tokens;

	bool quotes = false, brackets = false;
	size_t start = 0;

	for (size_t i = 0; i < line.size(); ++i) {
		char ch = line.at(i);

		if (i == line.size() - 1)
			tokens.push_back(line.substr(start, i - start + 1));

		else if (ch == '{')
			brackets = true;

		else if (ch == '}')
			brackets = false;

		else if (ch == '"')
			quotes = not quotes;

		else if (ch == delimeter && !quotes && !brackets) {
			tokens.push_back(line.substr(start, i - start));
			start = i + 1;
		}
	}

	return tokens;
}
