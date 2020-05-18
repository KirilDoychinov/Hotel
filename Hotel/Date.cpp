#include "Date.h"
#include <algorithm>

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

bool Date::operator <(const Date& dt) const {
	if (year < dt.year)
		return true;
	if (year == dt.year && (month < dt.month || (month == dt.month && day < dt.day)))
		return true;

	return false;
}

bool Date::operator==(const Date& dt) const {
	return year == dt.year && month == dt.month && day == dt.day;
}

bool Date::operator!=(const Date& dt) const {
	return !(*this == dt);
}

Date& Date::operator=(Date other)
{
	swap(*this, other);
	return *this;
}

int  Date::duration(const Date& dt) const {
	const int monthDays[12] = { 31, 28, 31, 30, 31, 30,
							   31, 31, 30, 31, 30, 31 };

	long int totalDays1 = this->year * 365 + this->day, totalDays2 = dt.year * 365 + dt.day;

	for (int i = 0; i < this->month - 1; ++i)
		totalDays1 += monthDays[i];

	adjustLeapYears(totalDays1, *this);
	adjustLeapYears(totalDays2, dt);

	return abs(totalDays1 - totalDays2);
}

void adjustLeapYears(long& days, const Date& date) {
	if (date.getMonth() <= 2)
		--days;

	int year = date.getYear();
	days += year / 4 - year / 100 + year / 400;
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

