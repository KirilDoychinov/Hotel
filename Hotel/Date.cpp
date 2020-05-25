#include "Date.h"
#include <algorithm>
#include <ctime>

void adjustLeapYears(long&, const Date&);

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
}

Date::~Date() {
}

int Date::getDay() const {
	return this->day;
}

int Date::getMonth() const {
	return this->month;
}

int Date::getYear() const {
	return this->year;
}

Date& Date::operator=(Date other)
{
	swap(*this, other);
	return *this;
}

int  duration(const Date& lhs, const Date& rhs) {
	const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
							   31, 31, 30, 31, 30, 31 };

	long int lhsDaysElapsed = lhs.year * 365 + lhs.day, rhsDaysElapsed = rhs.year * 365 + rhs.day;

	for (int i = 0; i < lhs.month - 1; ++i)
		lhsDaysElapsed += monthDays[i];

	adjustLeapYears(lhsDaysElapsed, lhs);
	adjustLeapYears(rhsDaysElapsed, rhs);

	return abs(lhsDaysElapsed - rhsDaysElapsed);
}

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
	os << dt.year << '-' << dt.month << '-' << dt.day;
	return os;
}

void swap(Date& first, Date& second) {
	std::swap(first.day, second.day);
	std::swap(first.month, second.month);
	std::swap(first.year, second.year);
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
	time_t now = std::time(0);
	tm* time = std::localtime(&now);

	int year = 1900 + time->tm_year;
	int month = 1 + time->tm_mon;
	int day = time->tm_mday;

	return new Date(day, month, year);
}

void adjustLeapYears(long& days, const Date& date) {
	if (date.getMonth() <= 2)
		--days;

	int year = date.getYear();
	days += year / 4 - year / 100 + year / 400;
}
