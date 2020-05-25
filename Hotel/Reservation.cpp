#include "Reservation.h"

Reservation::Reservation(const Date& start, const Date& end, const std::string& note, int guests) :
	start(start), end(end), note(note), guests(guests), activities(std::set<Activity>()) {
}

Reservation::~Reservation() {
}

Date Reservation::getStart() const {
	return start;
}

Date Reservation::getEnd() const {
	return end;
}
int Reservation::getGuests() const {
	return guests;
}

std::string Reservation::getNote() const {
	return note;
}

std::set<Activity>  Reservation::getActivities() const {
	return activities;
}

int Reservation::calculateDuration() const {
	return duration(start, end);
}

void  Reservation::addActivity(Activity& activity) {
	activities.insert(activity);
}

std::ostream& operator<<(std::ostream& os, const Reservation& reservation) {
	std::string separator = " ";

	os << "{";
	os << reservation.getStart() << separator << reservation.getEnd() << separator << "\"" << reservation.getNote() << "\" " << separator << reservation.getGuests();
	os << "}";

	return os;
}

