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
	int duration(const Date&) const;

	bool operator <(const Date&) const;
	bool operator==(const Date&) const;
	bool operator!=(const Date&) const;
	Date& operator=(Date other);

	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend void swap(Date& first, Date& second);

private:
	int day;
	int month;
	int year;
};

#endif

