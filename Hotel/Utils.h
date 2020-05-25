#ifndef UTILS_H
#define UTILS_H

#include "Date.h"
#include "Reservation.h"
#include <string>
#include <optional>

namespace Utils
{
	bool isDigit(char);
	bool isLeapYear(int);
	void trim(std::string&);

	bool isNaturalNumber(const std::string&);
	std::optional<Date*> isDate(const std::string&);	
	std::optional<Reservation*> isReservation(const std::string&);
	
};

#endif

