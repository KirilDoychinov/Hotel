#include "Room.h"
#include <cassert>

Room::Room(int number, int capacity) : number(number), capacity(capacity), reservations(std::vector<Reservation*>()) {
}

Room::~Room() {
}

bool Room::reserve(const Date& start, const Date& end, const std::string& note, int numberOfGuests = 0) {
	Reservation* newReservation = new Reservation(start, end, note, numberOfGuests);

	if (reservations.empty() || reservations.back()->getEnd < start)
		reservations.push_back(newReservation);

	else
		for (int i = 0; i < reservations.size(); ++i) {
			Reservation* reservation = reservations[i];
			if (end < reservation->getStart()) {
				reservations.insert(reservations.begin() + i, newReservation);
				break;
			}
			if (start <= reservation->getEnd())
				return false;
		}

	return true;
}

bool Room::isFree(const Date& date) {

	for (Reservation* reservation : reservations) {
		if (reservation->getStart() <= date && date <= reservation->getEnd())
			return false;
		if (reservation->getStart() > date)
			break;
	}

	return true;
}

bool Room::isFree(const Date& start, const Date& end) {
	assert(end >= start);

	for (auto& reservation : reservations) {
		if (end < reservation->getStart())
			break;
		if (start <= reservation->getEnd())
			return false;
	}

	return true;
}

int Room::countDaysInUse(const Date& start, const Date& end) {

	int days = 0;

	for (Reservation* reservation : reservations) {
		if (reservation->getStart() > end)
			break;
		if (reservation->getEnd() >= start) {
			Date intersectionStart = reservation->getStart() > start ? reservation->getStart() : start;
			Date intersectionEnd = reservation->getEnd() < end ? reservation->getEnd() : end;
			days += duration(intersectionStart, intersectionEnd);

		}
	}

	return days;
}

std::ostream& operator<<(std::ostream& os, const Room& room) {

	os << room.number << " " << room.capacity << " {";

	size_t len = room.reservations.size();
	for (size_t i = 0; i < len; ++i) {
		Reservation* current = room.reservations.at(i);
		os << current;
		if (i != len - 1)
			os << ",";
	}

	os << "}" << std::endl;

	return os;
}
