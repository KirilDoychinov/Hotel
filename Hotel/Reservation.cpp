#include "Reservation.h"

Reservation::Reservation(const Date& start, const Date& end, const std::string& note, int guests) :
	start(start), end(end), note(note), guests(guests) {
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

int Reservation::calculateDuration() const {
	return duration(start, end);
}

std::ostream& operator<<(std::ostream& os, const Reservation& reservation) {

	os << "{";
	os << reservation.getStart() << " " << reservation.getEnd() << reservation.getNote() << " " << reservation.getGuests();
	os << "}";

	return os;
}

