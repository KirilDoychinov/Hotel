#include "Room.h"
#include <optional>

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
			else if (*start <= temp->getEnd()) {
				delete reservation;
				return false;
			}
		}

	return true;
}

std::optional<Reservation*> Room::findReservation(Date* date) const {
	for (Reservation* reservation : reservations) {
		if (reservation->getStart() <= *date && *date <= reservation->getEnd())
			return reservation;
		if (reservation->getStart() > * date)
			break;
	}

	return {};
}


bool Room::isFree(Date* date) const {
	return !findReservation(date).has_value();
}

bool Room::isFree(Date* start, Date* end) const {
	for (auto reservation : reservations) {
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

void Room::free() {
	Date today = *Date::today();

	for (size_t i = 0; i < reservations.size(); ++i) {
		Reservation* current = reservations.at(i);
		if (current->getStart() <= today && today <= current->getEnd()) {
			delete reservations.at(i);
			reservations.erase(reservations.begin() + i);
			std::cout << "Room was succesfully freed!" << std::endl;
			return;
		}
	}

	std::cout << "Room is already free and waiting for guests!" << std::endl;
}

void Room::subscribe(std::string& activity) {
	auto reservation = findReservation(Date::today());
	if (reservation.has_value())
		reservation.value()->addActivity(activity);
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