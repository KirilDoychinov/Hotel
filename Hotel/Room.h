#ifndef ROOM_H
#define ROOM_H

#include "Reservation.h"
#include "Date.h"
#include <vector>
#include <string>
#include <optional>

/**
 * @class  Room
 *
 * @brief  Class Representing an hotel room with given number, capacity and 
 * 		   list of hotel reservations for the room
 */

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
	/**
	* Room number
	*/
	int number;

	/**
	* Room capacity
	*/
	int capacity;

	/**
	* List of reservations made for the room
	*/
	std::vector<Reservation*> reservations;
};

#endif

