#ifndef DATE_H
#define DATE_H

#include <fstream>

/**
 * @class	Date
 *
 * @brief	Class representing a calender date with days, months and years after
 * 			AD (Anno Domini, or 0 years onwards) using Gregorian calendar
 */

class Date
{
public:
	Date(unsigned int day, unsigned int month, unsigned int year);
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
	friend bool validate(const Date& first, const Date& second);

	static Date* today();

private:
	/**
	 * Calendar day (1-31)
	 */
	unsigned int day;

	/**
	 * Calendar month (1-12)
	 */
	unsigned int month;

	/**
	 * Calendar year (0- onwards)
	 */
	unsigned int year;
};

#endif

