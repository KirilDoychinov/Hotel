#ifndef DATE_H
#define DATE_H

#include <fstream>

class Date
{
public:
	Date(int day, int month, int year);
	Date(const Date& other);
	~Date();

	friend bool operator <(const Date& lhs, const Date& rhs);
	friend bool operator >(const Date& lhs, const Date& rhs);
	friend bool operator<=(const Date& lhs, const  Date& rhs);
	friend bool operator>=(const  Date& lhs, const  Date& rhs);
	friend bool operator==(const Date& lhs, const Date& rhs);
	friend bool operator!=(const Date& lhs, const Date& rhs);

	Date& operator=(Date other);

	friend std::ostream& operator<<(std::ostream& os, const Date& date);
	friend void swap(Date& first, Date& second);
	friend long duration(const Date& first, const Date& second);

	static Date* today();

private:
	int day;
	int month;
	int year;
};

#endif

