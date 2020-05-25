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
	Room(int, int, std::vector<Reservation*>&);
	~Room();

	int getNumber() const;
	int getCapacity() const;
	std::vector<Reservation*> getReservations() const;

	bool reserve( Reservation*);
	bool isFree(const Date&);
	bool isFree(const Date& start, const Date& end);
	void free();
	int countDaysInUse(const Date& start, const Date& end);
	Reservation* getCurrentReservation();

	friend std::ostream& operator<<(std::ostream&, const Room&);

private:
	int number;
	int capacity;
	std::vector<Reservation*> reservations;
};

#endif

