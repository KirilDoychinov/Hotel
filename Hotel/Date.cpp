#include "Date.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

int countLeapYears(unsigned  int, int);
void acumulateDays(long&, unsigned int);

/**
 * @brief	            Creates new Date from given day, month and year

 * @param [in] 	day  	The day of the date
 *
 * @param [in] 	month	The month of the date
 *
 * @param [in] 	year 	The year of the date
 *
 */

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {
}

/**
 * @brief	            Copy constructor
 *
 * @param [in]	other   Date object to be copied from
 *
 */

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
}

/**
 * @brief	Default object destructor
 *
 */

Date::~Date() {
}

/**
 * @brief	            Assignment operator for date objects
 *
 * @param [in] 	other	Date object to be assigned to
 *
 * @returns	            A shallow copy of this object.
 *
 */

Date& Date::operator=(Date other)
{
	swap(*this, other);
	return *this;
}

/**
 * @brief	        Calculates absolute duration in days between two given dates
 *
 * @param 	first 	First date
 *
 * @param 	second	Second date
 *
 * @returns	        Absolute number of days between the two given dates
 *
 */

long duration(const Date& first, const Date& second) {
	long totalDays1 = first.year * 365 + first.day, totalDays2 = second.year * 365 + second.day;

	acumulateDays(totalDays1, first.month);
	acumulateDays(totalDays2, second.month);

	return abs(totalDays2 + countLeapYears(second.month, second.year) - totalDays1 - countLeapYears(first.month, first.year));
}

/**
 * @brief	          Less-than comparison operator
 *
 * @param [in] 	lhs	  The first instance to compare.
 *
 * @param [in] 	rhs	  The second instance to compare.
 *
 * @returns	          True if the first date is chronologically after the second
 *
 */

bool operator <(const Date& lhs, const Date& rhs) {
	if (lhs.year < rhs.year ||
		(lhs.year == rhs.year && lhs.month < rhs.month) ||
		(lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day))
		return true;
	return false;
}

/**
 * @brief	          Greater-than comparison operator
 *
 * @param [in] 	lhs	  The first instance to compare.
 *
 * @param [in] 	rhs	  The second instance to compare.
 *
 * @returns	          True if the first date is chronologically after the second
 *
 */

bool operator >(const Date& lhs, const Date& rhs) {
	return rhs < lhs;
}

/**
 * @brief	          Less-than-or-equal comparison operator
 *
 * @param [in] 	lhs	  The first instance to compare.
 *
 * @param [in] 	rhs	  The second instance to compare.
 *
 * @returns	          True if the first date is chronologically before or matches the second
 *
 */

bool operator<=(const Date& lhs, const  Date& rhs) {
	return !(lhs > rhs);
}

/**
 * @brief	          Greater-than-or-equal comparison operator
 *
 * @param [in] 	lhs	  The first instance to compare.
 *
 * @param [in] 	rhs	  The second instance to compare.
 *
 * @returns	          True if the first date is chronologically after or matches the second
 *
 */

bool operator>=(const  Date& lhs, const  Date& rhs) {
	return !(lhs < rhs);
}

/**
 * @brief	         Equality operator for date objects
 *
 * @param [in] 	lhs	 The first instance to compare.
 *
 * @param [in] 	rhs	 The second instance to compare.
 *
 * @returns	         True if the dates represent the calendar date
 *
 */

bool operator ==(const Date& lhs, const Date& rhs) {
	return lhs.day == rhs.day && lhs.month == rhs.month && lhs.year == rhs.year;
}

/**
 * @brief	         Inequality operator for dates
 *
 * @param [in] 	lhs	 The first instance to compare.
 *
 * @param [in] 	rhs	 The second instance to compare.
 *
 * @returns	         True if the parameters are not considered equivalent calendar dates
 *
 */

bool operator !=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

/**
 * @brief	 return Date pointer for today' date
 *
 * @returns	 Null if it fails, else a pointer to a Date
 * 			repesenting the current local calendar date
 *
 */

Date* Date::today() {
	struct tm time;
	time_t now = std::time(nullptr);
	localtime_s(&time, &now);
	int day = time.tm_mday;
	int month = 1 + time.tm_mon;
	int year = 1900 + time.tm_year;

	return new Date(day, month, year);
}

/**
 * @brief	               Stream insertion operator for Date objects
 *
 * @param [in,out]   os	   The output stream
 *
 * @param [in] 	     date  Date to be streamed
 *
 * @returns	               The streamed date object
 */

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	char separator = '-';
	os << date.year << separator;

	if (date.month < 10)
		os << "0";
	os << date.month << separator;

	if (date.day < 10)
		os << "0";
	os << date.day;

	return os;
}

/**
 * @brief	            Swaps the values of two dates
 *
 * @param [in] 	first	First date
 *
 * @param [in] 	second	Second date
 */

void swap(Date& first, Date& second) {
	std::swap(first.day, second.day);
	std::swap(first.month, second.month);
	std::swap(first.year, second.year);
}

/**
 * @brief	             Check if two dates are given in correct chronological order
 * 			             and print error message in case not
 *
 * @param [in] 	first 	 The first date
 *
 * @param [in] 	second	 The second date
 *
 * @returns	             True if the first date is chronologically before
 * 			             the second and false otherwise
 */

bool validate(const Date& first, const Date& second) {
	if (first > second) {
		std::cout << "Invalid dates! End date should be after the starting one!" << std::endl;
		return false;
	}
	return true;
}

/**
 * @brief	            Count leap years passed to given year and month
 *
 * @param [in] 	month	Month of the date
 *
 * @param [in] 	year 	Year of the date
 *
 * @returns	            The total number of leap years from AD to the given date
 */

int countLeapYears(unsigned int month, int year) {
	if (month <= 2 && year > 0)
		--year;

	return year / 4 - year / 100 + year / 400;
}

/**
 * @brief	               Acumulate days elapsed from the start of an year up to given month
 *
 * @param [in,out]	days   The days we will count
 *
 * @param [in]		month  The month to stop counting elapsed days
 */

void acumulateDays(long& days, unsigned int month) {
	const unsigned int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };

	for (int i = 0; i < month - 1; ++i)
		days += daysPerMonth[i];
}
