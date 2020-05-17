#include <fstream>

#ifndef DATE_H
#define DATE_H

class Date
{
public:
	Date(int, int, int);
	~Date();

	int getDay() const;
	int getMonth() const;
	int getYear() const;

	friend std::ostream& operator<<(std::ostream&, const Date&);
	bool operator <(const Date&) const;
	bool operator==(const Date&) const;
	bool operator!=(const Date&) const;
	int duration(const Date&) const;

private:
	int day;
	int month;
	int year;
};

#endif

