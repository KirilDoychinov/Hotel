#include "Room.h"
#include <cassert>

Room::Room(int number, int capacity) : number(number), capacity(capacity), reservations(std::vector<Reservation*>()) {
}

Room::Room(int number, int capacity, std::vector<Reservation*>& reservations) : number(number), capacity(capacity), reservations(reservations) {
}

Room::~Room() {
}

int Room::getNumber() const {
	return number;
}

int Room::getCapacity() const {
	return capacity;
}

std::vector<Reservation*> Room::getReservations() const {
	return reservations;
}

bool Room::reserve(Reservation* reservation) {
	Date start = reservation->getStart(), end = reservation->getEnd();

	if (reservations.empty() || reservations.back()->getEnd() < start)
		reservations.push_back(reservation);

	else
		for (int i = 0; i < reservations.size(); ++i) {
			Reservation* reservation = reservations[i];
			if (end < reservation->getStart()) {
				reservations.insert(reservations.begin() + i, reservation);
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

Reservation* Room::getCurrentReservation() {
	Date today = *Date::today();
	for (Reservation* reservation : reservations) {
		if (reservation->getStart() <= today && today <= reservation->getEnd())
			return  reservation;
	}

	return nullptr;
}

std::ostream& operator<<(std::ostream& os, const Room& room) {

	std::string separator = " ";
	os << room.number << separator << room.capacity;

	size_t len = room.reservations.size();
	for (size_t i = 0; i < len; ++i) {
		Reservation* current = room.reservations.at(i);
		os << separator << current;
	}

	os << std::endl;
	return os;
}

void Room::free() {
	Date today = *Date::today();
	int currentReservationIndex = -1;

	for (size_t i = 0; i < reservations.size(); ++i) {
		Reservation* current = reservations.at(i);
		if (current->getStart() <= today && today <= current->getEnd()) {
			currentReservationIndex = i;
			break;
		}
	}

	if (currentReservationIndex != -1)
		reservations.erase(reservations.begin() + currentReservationIndex);
}


