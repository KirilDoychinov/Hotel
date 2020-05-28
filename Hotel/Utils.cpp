#include "Utils.h"

void Utils::trim(std::string& str) {
	if (str.empty())
		return;

	std::string spaceCharacters = " \t\f\v\n\r";

	std::size_t start = str.find_first_not_of(spaceCharacters);
	std::size_t end = str.std::string::find_last_not_of(spaceCharacters);

	if (start != std::string::npos)
		str = str.substr(start, end - start + 1);
}