#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"
#include <fstream>
#include <string>

class Reservation
{
public:
	Reservation(const Date&, const Date& , const std::string&, int = 0);
	~Reservation();

	Date getStart() const;
	Date getEnd() const;
	int getGuests() const;
	std::string getNote() const;

	int calculateDuration() const;

	friend std::ostream& operator<<(std::ostream&, const Reservation&);
	
private:
	Date start;
	Date end;
	int guests;
	std::string note;

};

#endif

