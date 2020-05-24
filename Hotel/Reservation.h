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
	Reservation(const Date&, const Date& , const std::string&, int = 0);
	~Reservation();

	Date getStart() const;
	Date getEnd() const;
	int getGuests() const;
	std::string getNote() const;
	std::set<Activity> getActivities() const;

	int calculateDuration() const;
	void addActivity(Activity&);

	friend std::ostream& operator<<(std::ostream&, const Reservation&);
	
private:
	Date start;
	Date end;
	int guests;
	std::string note;
	std::set<Activity> activities;

};

#endif

