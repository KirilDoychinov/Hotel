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

	void reserve(const Date&, const Date&, const std::string&);

	void reserve(const Date&, const Date&, const std::string&, int);

	bool isFree(const Date&);

	bool isFree(const Date& start, const Date& end);

	int countDaysInUse(const Date& start, const Date& end);

private:
	int number;
	int capacity;
	std::vector<Reservation*> reservations;
};

#endif

