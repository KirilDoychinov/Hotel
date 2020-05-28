#ifndef RESERVATION_H
#define RESERVATION_H

#include "Date.h"
#include <fstream>
#include <string>
#include <set>
#include "Activity.h"

class Reservation
{
public:
	Reservation(Date* start, Date* end, std::string& note, int guests = 0);
	~Reservation();

	const Date& getStart() const;
	const Date& getEnd() const;
	const std::string& getNote() const;
	const std::set<Activity>& getActivities() const;
	int getGuests() const;

	int calculateDuration() const;
	void addActivity(std::string& activity);

	friend std::ostream& operator<<(std::ostream& os, const Reservation& reservation);

private:
	Date* start;
	Date* end;
	int guests;
	std::string note;
	std::set<Activity> activities;
};

#endif

