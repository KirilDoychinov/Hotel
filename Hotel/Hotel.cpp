#include "Hotel.h"
#include "Room.h"
#include <iostream>

Hotel::Hotel() : rooms(std::vector<Room*>()) {
}

Hotel::~Hotel() {
	for (auto room : rooms) {
		delete room;
		room = nullptr;
	}
}

bool Hotel::empty() const {
	return rooms.size() == 0;
}

bool Hotel::hasRoom(int room) const {
	return findRoom(room) != nullptr;
}

void Hotel::addRoom(int number, int capacity) {
	rooms.push_back(new Room(number, capacity));
}

Room* Hotel::findRoom(int number) const {
	for (auto room : rooms)
		if (room->getNumber() == number)
			return room;

	return nullptr;
}

void Hotel::availability(Date* date) const {
	for (auto room : rooms)
		if (room->isFree(date))
			std::cout << room->getNumber() << " with capacity " << room->getCapacity() << std::endl;
}

void Hotel::makeReservation(int roomNumber, Date* start, Date* end, std::string& note, int guests) {
	auto room = findRoom(roomNumber);

	if (room != nullptr) {
		room->reserve(start, end, note, guests == -1 ? room->getCapacity() : guests);
	}
	else
		std::cout << "Room does not exist!" << std::endl;
}

void  Hotel::emptyRoom(int roomNumber) {
	Room* room = findRoom(roomNumber);
	if (room != nullptr)
		room->free();
}

void  Hotel::report(Date* start, Date* end) const {
	for (auto room : rooms) {
		int daysInUse = room->countDaysInUse(start, end);
		if (daysInUse > 0)
			std::cout << room->getNumber() << " used for " << daysInUse << " days" << std::endl;
	}
}

int Hotel::findRoom(int beds, Date* start, Date* end) const {
	int indexBestRoom = -1, minCapacity = INT_MAX;
	for (auto room : rooms) {
		int capacity = room->getCapacity();
		if (capacity >= beds && room->isFree(start, end))
			if (capacity < minCapacity) {
				minCapacity = capacity;
				indexBestRoom = room->getNumber();
			}
	}

	return indexBestRoom;
}

void Hotel::printRoomActivities(int roomNumber) const {
	Room* room = findRoom(roomNumber);

	if (room != nullptr) {
		Reservation* r = room->getCurrentReservation();
		if (r != nullptr)
			for (const Activity& a : r->getActivities())
				std::cout << a << std::endl;
	}
}

void Hotel::printSubs(const Activity& activity)  const {
	for (auto room : rooms) {
		Reservation* currentReservation = room->getCurrentReservation();
		if (currentReservation != nullptr) {
			if (currentReservation->getActivities().find(activity) != currentReservation->getActivities().end())
				std::cout << room->getNumber() << std::endl;
		}
	}
}

void Hotel::addActivity(int room, std::string& activity) {
	Room* room = findRoom(room);

	if (room != nullptr) {
}

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
	for (auto room : hotel.rooms)
		os << *room;

	return os;
}
