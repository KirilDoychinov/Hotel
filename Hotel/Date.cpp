#include "Date.h"
#include <algorithm>
#include <ctime>
#include <iostream>

int countLeapYears(int, int);
void accumulateDays(long&, int);

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
}

Date::~Date() {
}

Date& Date::operator=(Date other)
{
	swap(*this, other);
	return *this;
}

long duration(const Date& first, const Date& second) {
	long totalDays1 = first.year * 365 + first.day, totalDays2 = second.year * 365 + second.day;

	accumulateDays(totalDays1, first.month);
	accumulateDays(totalDays2, second.month);

	return totalDays1 + countLeapYears(first.month, first.year) - totalDays2 - countLeapYears(second.month, second.year);
}

bool operator <(const Date& lhs, const Date& rhs) {
	if (lhs.year < rhs.year ||
		(lhs.year == rhs.year && lhs.month < rhs.month) ||
		(lhs.year == rhs.year && lhs.month == rhs.month && lhs.day < rhs.day))
		return true;
	return false;
}

bool operator >(const Date& lhs, const Date& rhs) {
	return rhs < lhs;
}

bool operator<=(const Date& lhs, const  Date& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const  Date& lhs, const  Date& rhs) {
	return !(lhs < rhs);
}

bool operator ==(const Date& lhs, const Date& rhs) {
	return lhs.day == rhs.day && lhs.month == rhs.month && lhs.year == rhs.year;
}

bool operator !=(const Date& lhs, const Date& rhs) {
	return !(lhs == rhs);
}

Date* Date::today() {
	struct tm time;
	time_t now = std::time(nullptr);
	localtime_s(&time, &now);
	int day = time.tm_mday;
	int month = 1 + time.tm_mon;
	int year = 1900 + time.tm_year;
	
	return new Date(day, month, year);
}

int countLeapYears(int month, int year) {
	if (month <= 2)
		year--;

	return year / 4 - year / 100 + year / 400;
}

void accumulateDays(long& days, int month) {
	const int daysPerMonth[12] = { 31, 28, 31, 30, 31, 30,
						   31, 31, 30, 31, 30, 31 };

	for (int i = 0; i < month - 1; ++i)
		days += daysPerMonth[i];
}


std::ostream& operator<<(std::ostream& os, const Date& date)
{
	os << date.year << '-' << date.month << '-' << date.day;
	return os;
}

void swap(Date& first, Date& other) {
	std::swap(first.day, other.day);
	std::swap(first.month, other.month);
	std::swap(first.year, other.year);
}

bool validate(const Date& first, const Date& second) {
	if (first > second) {
		std::cout << "Invalid dates! End date should be after the starting one!" << std::endl;
		return false;
	}
	return true;
}
