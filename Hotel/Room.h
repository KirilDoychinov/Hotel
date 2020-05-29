#ifndef ROOM_H
#define ROOM_H

#include "Reservation.h"
#include "Date.h"
#include <vector>
#include <string>
#include <optional>

class Room
{

public:
	Room(int number, int capacity);
	~Room();

	int getNumber() const;
	int getCapacity() const;
	const std::vector<Reservation*>& getReservations() const;
	void reserve(Date* start, Date* end, std::string& note, int guests);

	bool isFree(Date* date = Date::today()) const;
	bool isFree(Date* start, Date* end) const;
	std::optional<Reservation*> findReservation(Date* date) const;

	void free();
	int countDaysInUse(Date* start, Date* end) const;
	void subscribe(std::string& activity);

	friend std::ostream& operator<<(std::ostream& os, const Room& room);

private:
	int number;
	int capacity;
	std::vector<Reservation*> reservations;
};

#endif

