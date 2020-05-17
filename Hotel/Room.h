#ifndef ROOM_H
#define ROOM_H

#include "Reservation.h"
#include <vector>
#include <ctime>
#include <string>

class Room
{

public:
	Room(int, int);
	~Room();

	void reserve(tm start, tm end, std::string note, int numberOfGuests);

	bool isFree(tm date);

	bool isFree(tm start, tm end);

	int countDaysInUse(tm start, tm end);




private:
	int number;
	int capacity;
	std::vector<Reservation*> reservations;
};

#endif

