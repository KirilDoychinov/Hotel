#include "Reservation.h"
#include <iostream>

/**
 * @brief	            Parametrized constructor for Reservation objects
 *
 * @param [in]  start 	The start date of the reservation
 *
 * @param [in]	end   	The end date of the reservation
 *
 * @param [in]	note    Note attached for this reservation
 *
 * @param [in]		  	guests	The number of guests
 *
 */

Reservation::Reservation(Date* start, Date* end, std::string& note, int guests) :
	start(start), end(end), note(note), guests(guests), activities(std::set < std::string >()) {
}

/**
 * @brief	Destructor for reservation objects
 */

Reservation::~Reservation() {
	delete start;
	delete end;
}

/**
 * @brief	Gets the start date of a reservation
 *
 * @returns	The start date or null if not present
 */

const Date& Reservation::getStart() const {
	return *start;
}

/**
 * @brief	Gets the end date of a reservation
 *
 * @returns	The end date or null if not present
 */

const Date& Reservation::getEnd() const {
	return *end;
}

/**
 * @brief	Gets the attached note of a reservation
 *
 * @returns	The note
 */

const std::string& Reservation::getNote() const {
	return note;
}

/**
 * @brief	Gets the activities a reservation has subscribed for
 *
 * @returns	The subscribed activities
 */

const std::set<std::string>& Reservation::getActivities() const {
	return activities;
}

/**
 * @brief	Gets the number of guests
 *
 * @returns	Number of guests
 */

int Reservation::getGuests() const {
	return guests;
}

/**
 * @brief	Calculates the duration of reservation in days
 *
 * @returns	Reservation length in days
 */

int Reservation::calculateDuration() const {
	return duration(*start, *end);
}

/**
 * @brief	               Subscribe the people from the current reservation for given activity
 *
 * @param [in]  activity   Activity to be subscribed
 */

void  Reservation::subscribe(std::string& activity) {
	if (activities.find(activity) == activities.end()) {
		activities.insert(activity);
		std::cout << "Succesfully subscribed for activity!" << std::endl;
	}
	else
		std::cout << "Room guests have already subscribed for this activity!" << std::endl;
}

/**
 * @brief	               Check if current reservation has subscribed for given activity
 *
 * @param [in]  activity   Activity to be checked
 *
 * @returns	               True if current reservation has subscription for this activity,
 * 			               otherwise
 */

bool Reservation::hasActivity(const std::string& activity) const {
	return activities.find(activity) != activities.end();
}

/**
 * @brief	                     Stream insertion operator for Reservation objects
 *
 * @param [in,out]  os	         The output stream
 *
 * @param [in]	    reservation  Reservation to be streamed
 *
 * @returns	                     The streamed reservation object
 */

std::ostream& operator<<(std::ostream& os, const Reservation& reservation) {
	std::string separator = " ";

	os << "{";
	os << reservation.getStart() << separator << reservation.getEnd() << separator << '"' << reservation.getNote() << '"' << separator << reservation.getGuests();
	os << "}";

	return os;
}

