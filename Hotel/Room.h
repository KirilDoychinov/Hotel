#ifndef ROOM_H
#define ROOM_H

#include "Reservation.h"
#include "Date.h"
#include <vector>
#include <string>

class Room
{

public:
	Room(int, int);
	~Room();

	bool reserve(const Date&, const Date&, const std::string&, int = 0);
	bool isFree(const Date&);
	bool isFree(const Date& start, const Date& end);
	int countDaysInUse(const Date& start, const Date& end);

	friend std::ostream& operator<<(std::ostream&, const Room&);

private:
	int number;
	int capacity;
	std::vector<Reservation*> reservations;
};

#endif

