#ifndef ROOM_H
#define ROOM_H

#include "Reservation.h"
#include "Date.h"
#include <vector>
#include <string>

class Room
{

public:
	Room(int number, int capacity);
	~Room();

	int getNumber() const;
	int getCapacity() const;
	const std::vector<Reservation*>& getReservations() const;
	bool reserve(Date* start, Date* end, std::string& note, int guests);
	bool isFree(Date* date) const;
	bool isFree(Date* start, Date* end) const;
	void free();
	int countDaysInUse(Date* start, Date* end) const;
	Reservation* getCurrentReservation() const;
	void subscribe(std::string& activity);

	friend std::ostream& operator<<(std::ostream& os, const Room& room);

private:
	int number;
	int capacity;
	std::vector<Reservation*> reservations;
};

#endif

