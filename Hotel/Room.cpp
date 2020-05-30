#include "Room.h"
#include <iostream>
#include <optional>

/**
 * @brief	    Constructs new room from given room number and a capacity
 *
 * @param [in] 	number  	Room number
 *
 * @param [in] 	capacity	Capacity
 *
 */

Room::Room(int number, int capacity) : number(number), capacity(capacity), reservations(std::vector<Reservation*>()) {
}

/**
 * @brief	Destructs the object deallocating dynamic memory
 *
 */

Room::~Room() {
	for (auto reservation : reservations)
		delete reservation;
}

/**
 * @brief	Gets the room number
 *
 * @returns	Returns the room number
 *
 */

int Room::getNumber() const {
	return number;
}

/**
 * @brief   Gets the capacity of the room
 *
 * @returns	The capacity of the room
 *
 */

int Room::getCapacity() const {
	return capacity;
}

/**
 * @brief	 Get current room' reservations
 *
 * @returns	 return list of reservations
 *
 */

const std::vector<Reservation*>& Room::getReservations() const {
	return reservations;
}

/**
 * @brief			    Make a reservation for this room for the given period,
 * 					    if the room is available and can accomodate the guests
 *
 * @param [in]  start 	Start date of reservation
 *
 * @param [in]  end   	End date of reservation
 *
 * @param [in]  note  	Attached note
 *
 * @param [in]	guests	Number of guests should be not greater than room capacity
 *
 */

void Room::reserve(Date* start, Date* end, std::string& note, int guests) {
	Reservation* reservation = new Reservation(start, end, note, guests);

	if (guests > capacity) {
		std::cout << "Error with reservation: " << *reservation << " Selected room is too small to acommodate " << guests << " guests!" << std::endl;
		delete reservation;
		return;
	}

	if (reservations.empty() || reservations.back()->getEnd() < *start)
		reservations.push_back(reservation);

	else
		for (int i = 0; i < reservations.size(); ++i) {
			Reservation* temp = reservations[i];

			if (*end < temp->getStart()) {
				reservations.insert(reservations.begin() + i, reservation);
				break;
			}

			else if (*start <= temp->getEnd()) {
				std::cout << "Error with reservation: " << *reservation << " Room is already reserved for the given period." << std::endl;
				delete reservation;
				return;
			}
		}

	std::cout << "Reservation was successful!" << std::endl;
}

/**
 * @brief			  Searches for existing reservation at the given date
 *
 * @param [in]  date  Date to be searched
 *
 * @returns			  The existing reservation at the given day, or empty value otherwise
 *
 */

std::optional<Reservation*> Room::findReservation(Date* date) const {
	for (Reservation* reservation : reservations) {
		if (reservation->getStart() <= *date && *date <= reservation->getEnd())
			return reservation;
		if (reservation->getStart() > * date)
			break;
	}

	return {};
}

/**
 * @brief			  Check if room is free for the given day
 *
 * @param [in]  date  Date to be checked, today date used if
 * 					  date is not given
 *
 * @returns			  True if free, false otherwise
 *
 */

bool Room::isFree(Date* date) const {
	return !findReservation(date).has_value();
}

/**
 * @brief			   Check if room is free in the given time period
 *
 * @param [in]  start  Start date of time period
 *
 * @param [in]	end    End date of time period
 *
 * @returns			   True if free, false otherwise
 *
 */

bool Room::isFree(Date* start, Date* end) const {
	for (auto reservation : reservations) {
		if (*end < reservation->getStart())
			break;
		if (*start <= reservation->getEnd())
			return false;
	}
	return true;
}

/**
 * @brief			   Count days in use of current room in a given time period
 *
 * @param [in]  start  Start date of time period
 *
 * @param [in]  end	   End date of time period
 *
 * @returns			   The total number of days in use
 *
 */

int Room::countDaysInUse(Date* start, Date* end) const {
	int days = 0;
	for (Reservation* reservation : reservations) {
		if (reservation->getStart() > * end)
			break;
		if (reservation->getEnd() >= *start) {
			Date intersectionStart = reservation->getStart() > * start ? reservation->getStart() : *start;
			Date intersectionEnd = reservation->getEnd() < *end ? reservation->getEnd() : *end;
			days += duration(intersectionStart, intersectionEnd);
		}
	}

	return days;
}

/**
 * @brief  Frees this room, removing the current reservation
 * 		   if it has one, printing relevant message on result
 */

void Room::free() {
	Date today = *Date::today();

	for (size_t i = 0; i < reservations.size(); ++i) {
		Reservation* current = reservations.at(i);
		if (current->getStart() <= today && today <= current->getEnd()) {
			delete reservations.at(i);
			reservations.erase(reservations.begin() + i);
			std::cout << "Room was succesfully freed!" << std::endl;
			return;
		}
	}

	std::cout << "Room is already free and waiting for guests!" << std::endl;
}

/**
 * @brief				  Subscribes the room guests for the given activity if rooms is
 * 						  occupied at the moment, printing relevant message on result
 *
 * @param [in]  activity  Activity to be subscribed for
 *
 */



void Room::subscribe(std::string& activity) {
	auto reservation = findReservation(Date::today());
	if (reservation.has_value())
		reservation.value()->subscribe(activity);
	else
		std::cout << "Room has no current guests to be subscribed for any activity!" << std::endl;
}

/**
 * @brief	              Stream insertion operator for Room objects
 *
 * @param [in,out]  os	  The output stream
 *
 * @param [in]	    room  Room to be streamed
 *
 * @returns	              The streamed room object
 *
 */

std::ostream& operator<<(std::ostream& os, const Room& room) {
	std::string separator = " ";
	os << room.number << separator << room.capacity;

	size_t len = room.reservations.size();
	for (size_t i = 0; i < len; ++i) {
		Reservation* current = room.reservations.at(i);
		os << separator << *current;
	}

	os << std::endl;
	return os;
}