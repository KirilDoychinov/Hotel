#include "Utils.h"

bool Utils::isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}

void Utils::trim(std::string& str) {
	if (str.empty())
		return;

	std::string spaceChars = " \t\f\v\n\r";

	std::size_t pos1 = str.find_first_not_of(spaceChars);
	std::size_t pos2 = str.std::string::find_last_not_of(spaceChars);

	if (pos1 != std::string::npos && pos2 != std::string::npos)
		str = str.substr(pos1, pos2 - pos1 + 1);
}

bool Utils::isNaturalNumber(const std::string& str) {
	for (size_t i = 0; i < str.size(); ++i)
		if (!isDigit(str.at(i)))
			return false;

	return true;
}

bool Utils::isLeapYear(int year) {
	if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))
		return false;

	return true;
}

std::optional<Date*> Utils::isDate(const std::string& str) {
	if (str.size() != 10)
		return std::nullopt;

	for (size_t i = 0; i < 10; ++i) {
		char ch = str.at(i);

		if (i == 4 || i == 7) {
			if (ch != '-')
				std::nullopt;
		}
		else if (!isDigit(ch))
			return std::nullopt;
	}

	int year = std::stoi(str.substr(0, 4));
	int month = std::stoi(str.substr(5, 2));
	int day = std::stoi(str.substr(8, 2));

	if (year < 1 || month < 1 || day < 1 || month > 12 || day > 31)
		return std::nullopt;

	if (month % 2 == 0) {
		int maxDays = 30;
		if (month == 2)
			maxDays = isLeapYear(year) ? 29 : 28;
		if (day > maxDays)
			return std::nullopt;
	}

	return new Date(day, month, year);
}

std::optional<Reservation*>  Utils::isReservation(const std::string& str) {
	if (str.size() < 26 || str.at(10) != ' ' || str.at(21) != ' ' || str.at(22) != '"')
		return  std::nullopt;

	auto date1 = isDate(str.substr(0, 10)), date2 = isDate(str.substr(11, 10));

	if (!date1.has_value() || !date2.has_value())
		return  std::nullopt;

	Date *start = date1.value(), *end = date2.value();

	size_t lastQuotePos = str.find_last_of("\"");
	if (lastQuotePos == 22 || lastQuotePos > str.size() - 3 || str.at(lastQuotePos + 1) != ' ')
		return  std::nullopt;

	std::string note = str.substr(23, lastQuotePos - 23);

	std::string capacity = str.substr(lastQuotePos + 2);
	if (!isNaturalNumber(capacity))
		return  std::nullopt;

	return new Reservation(*start, *end, note, std::stoi(capacity));
}
