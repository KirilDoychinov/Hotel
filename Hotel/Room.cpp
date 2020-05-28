#include "Room.h"
#include <cassert>

Room::Room(int number, int capacity) : number(number), capacity(capacity), reservations(std::vector<Reservation*>()) {
}

Room::~Room() {
	for (auto reservation : reservations)
		delete reservation;
}

int Room::getNumber() const {
	return number;
}

int Room::getCapacity() const {
	return capacity;
}

const std::vector<Reservation*>& Room::getReservations() const {
	return reservations;
}

bool Room::reserve(Date* start, Date* end, std::string& note, int guests) {
	Reservation* reservation = new Reservation(start, end, note, guests);

	if (reservations.empty() || reservations.back()->getEnd() < *start)
		reservations.push_back(reservation);

	else
		for (int i = 0; i < reservations.size(); ++i) {
			Reservation* temp = reservations[i];
			if (*end < temp->getStart()) {
				reservations.insert(reservations.begin() + i, reservation);
				break;
			}
			if (*start <= temp->getEnd())
				return false;
		}

	return true;
}

bool Room::isFree(Date* date) const {

	for (Reservation* reservation : reservations) {
		if (reservation->getStart() <= *date && *date <= reservation->getEnd())
			return false;
		if (reservation->getStart() > * date)
			break;
	}

	return true;
}

bool Room::isFree(Date* start, Date* end) const {
	assert(end >= start);

	for (auto& reservation : reservations) {
		if (*end < reservation->getStart())
			break;
		if (*start <= reservation->getEnd())
			return false;
	}

	return true;
}

int Room::countDaysInUse(Date* start, Date* end) const {

	int days = 0;

	for (Reservation* reservation : reservations) {
		if (reservation->getStart() > * end)
			break;
		if (reservation->getEnd() >= *start) {
			Date intersectionStart = reservation->getStart() > * start ? reservation->getStart() : *start;
			Date intersectionEnd = reservation->getEnd() < *end ? reservation->getEnd() : *end;
			days += duration(intersectionStart, intersectionEnd);

		}
	}

	return days;
}

Reservation* Room::getCurrentReservation() const {
	Date today = *Date::today();
	for (Reservation* reservation : reservations) {
		if (reservation->getStart() <= today && today <= reservation->getEnd())
			return  reservation;
	}

	return nullptr;
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

void Room::subscribe(std::string& activity) {
	Reservation* current = getCurrentReservation();
	if (current != nullptr)
		current->addActivity(activity);
}

std::ostream& operator<<(std::ostream& os, const Room& room) {

	std::string separator = " ";
	os << room.number << separator << room.capacity;

	size_t len = room.reservations.size();
	for (size_t i = 0; i < len; ++i) {
		Reservation* current = room.reservations.at(i);
		os << separator << *current;
	}

	os << std::endl;
	return os;
}