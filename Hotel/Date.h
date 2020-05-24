#ifndef DATE_H
#define DATE_H

#include <fstream>

class Date
{
public:
	Date(int, int, int);
	Date(const Date&);
	~Date();

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	friend bool operator <(const Date&, const Date&);
	friend bool operator >(const Date&, const Date&);
	friend bool operator<=(const Date&, const  Date&);
	friend bool operator>=(const  Date&, const  Date&);
	friend bool operator==(const Date&, const Date&);
	friend bool operator!=(const Date&, const Date&);
	
	Date& operator=(Date);

	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend void swap(Date& first, Date& second);
	friend int duration(const Date&, const Date&);

	static Date* today();

private:
	int day;
	int month;
	int year;
};

#endif

