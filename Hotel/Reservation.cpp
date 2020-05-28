#include "Reservation.h"

Reservation::Reservation(Date* start, Date* end, std::string& note, int guests) :
	start(start), end(end), note(note), guests(guests), activities(std::set < std::string > ()) {
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

const std::set<std::string>& Reservation::getActivities() const {
	return activities;
}

int Reservation::getGuests() const {
	return guests;
}

int Reservation::calculateDuration() const {
	return duration(*start, *end);
}

void  Reservation::addActivity(std::string& activity) {
	activities.insert(activity);
}

bool Reservation::hasActivity(const std::string& activity) const {
	return activities.find(activity) != activities.end();
}

std::ostream& operator<<(std::ostream& os, const Reservation& reservation) {
	std::string separator = " ";

	os << "{";
	os << reservation.getStart() << separator << reservation.getEnd() << separator << "\"" << reservation.getNote() << "\" " << separator << reservation.getGuests();
	os << "}";

	return os;
}

