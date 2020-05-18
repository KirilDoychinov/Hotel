#include "Room.h"

Room::Room(int number, int capacity) : number(number), capacity(capacity), reservations(std::vector<Reservation*>()) {
}

Room::~Room() {
}

void Room::reserve(const Date& start, const Date& end, const std::string& note) {

}

void reserve(const Date& start, const Date& end, std::string& note, int numberOfGuests) {

}

bool isFree(const Date& date) {
	return true;

}

bool isFree(const Date& start, const Date& end) {
	return true;

}

int countDaysInUse(const Date& start, const Date& end) {

	return 0;
}