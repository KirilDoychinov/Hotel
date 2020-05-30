#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"
#include <fstream>
#include <string>
#include <set>

/**
 * @class	 Reservation
 *
 * @brief	 Class representing a hotel reservation entity with
 * 			 start and end dates, number of guests,
 * 			 a text note and list of subscribed hotel activities
 */

class Reservation
{
public:
	Reservation(Date* start, Date* end, std::string& note, int guests = 0);
	~Reservation();

	const Date& getStart() const;
	const Date& getEnd() const;
	const std::string& getNote() const;
	const std::set<std::string>& getActivities() const;
	int getGuests() const;

	int calculateDuration() const;
	void subscribe(std::string& activity);
	bool hasActivity(const std::string& activity) const;

	friend std::ostream& operator<<(std::ostream& os, const Reservation& reservation);

private:
	/**
	 * Starting Date of reservation
	 */
	Date* start;

	/**
	 * End Date of reservation
	 */
	Date* end;

	/**
	 * Number of guests
	 */
	int guests;

	/**
	 * Note 
	 */
	std::string note;

	/**
	 * List of subscribed activities
	 */
	std::set<std::string> activities;
};

#endif

