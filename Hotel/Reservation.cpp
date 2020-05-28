#include "Reservation.h"

Reservation::Reservation(Date* start, Date* end, std::string& note, int guests) :
	start(start), end(end), note(note), guests(guests), activities(std::set<Activity>()) {
}

Reservation::~Reservation() {
	delete start;
	delete end;
}

const Date& Reservation::getStart() const {
	return *start;
}

const Date& Reservation::getEnd() const {
	return *end;
}

const std::string& Reservation::getNote() const {
	return note;
}

const std::set<Activity>& Reservation::getActivities() const {
	return activities;
}

int Reservation::getGuests() const {
	return guests;
}

int Reservation::calculateDuration() const {
	return duration(*start, *end);
}

void  Reservation::addActivity(std::string& activity) {
	Activity* a = new Activity(activity);
	if (activities.find(*a) == activities.end())
		activities.insert(*a);
}

std::ostream& operator<<(std::ostream& os, const Reservation& reservation) {
	std::string separator = " ";

	os << "{";
	os << reservation.getStart() << separator << reservation.getEnd() << separator << "\"" << reservation.getNote() << "\" " << separator << reservation.getGuests();
	os << "}";

	return os;
}

