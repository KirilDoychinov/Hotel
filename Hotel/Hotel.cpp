#include "Hotel.h"
#include "Room.h"
#include <iostream>

Hotel::Hotel() : rooms(std::vector<Room*>()) {
}

Hotel::~Hotel() {
	for (auto& room : rooms)
		delete room;
}

void Hotel::addRoom(Room* room) {
	rooms.push_back(room);
}

Room* Hotel::findRoom(int number) {
	for (auto& room : rooms)
		if (room->getNumber() == number)
			return room;

	return nullptr;
}

void Hotel::addReservation(int number, Reservation* reservation) {
	findRoom(number)->reserve(reservation);
}

void Hotel::availability(const Date& date) {
	for (auto& room : rooms)
		if (room->isFree(date))
			std::cout << room->getNumber() << " with capacity " << room->getCapacity() << std::endl;
}

void  Hotel::checkout(int number) {
	findRoom(number)->free();
}

void  Hotel::report(const Date& start, const Date& end) {
	for (auto& room : rooms) {
		int daysInUse = room->countDaysInUse(start, end);
		if (daysInUse > 0) {
			std::cout << room->getNumber() << " used for " << daysInUse << " days" << std::endl;
		}

	}
}

int Hotel::findRoom(int bedsNeeded, const Date& start, const Date& end) {
	int bestRoom = -1, minCapacity = INT_MAX;
	for (auto& room : rooms) {
		int capacity = room->getCapacity();
		if (capacity >= bedsNeeded && room->isFree(start, end))
			if (capacity < minCapacity) {
				minCapacity = capacity;
				bestRoom = room->getNumber();
			}
	}

	return bestRoom;
}

void Hotel::printRoomActivities(int roomNumber) {
	Room* room = findRoom(roomNumber);

	if (room != nullptr) {
		Reservation* r = room->getCurrentReservation();
		if (r != nullptr)
			for (Activity a : r->getActivities())
				std::cout << a << std::endl;
	}
}

void Hotel::printAllSubscribedFor(Activity& activity) {
	for (auto room : rooms) {
		Reservation* currentRes = room->getCurrentReservation();
		if (currentRes != nullptr) {
			auto subscribedActivities = currentRes->getActivities();
			if (currentRes->getActivities().find(activity) != currentRes->getActivities().end())
				std::cout << room->getNumber() << std::endl;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
	for (auto* room : hotel.rooms)
		os << *room;
}
