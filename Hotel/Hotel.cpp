#include "Hotel.h"
#include "Room.h"
#include <iostream>
#include <optional>

Hotel::Hotel() : rooms(std::vector<Room*>()) {
}

Hotel::~Hotel() {
	for (auto room : rooms) {
		delete room;
		room = nullptr;
	}
}

bool Hotel::isEmpty() const {
	return rooms.size() == 0;
}

bool Hotel::hasRoom(int number) const {
	return findRoom(number) != nullptr;
}

std::optional<Room*> Hotel::getRoom(int roomNumber) const {
	auto room = findRoom(roomNumber);
	if (room == nullptr) {
		std::cout << "Room with number " << roomNumber << " does not exist!" << std::endl;
		return {};
	}
	return room;
}

void Hotel::addRoom(int roomNumber, int capacity) {
	if (!hasRoom(roomNumber))
		rooms.push_back(new Room(roomNumber, capacity));
}

Room* Hotel::findRoom(int number) const {
	for (auto room : rooms)
		if (room->getNumber() == number)
			return room;

	return nullptr;
}

void Hotel::printAvailableRooms(Date* date) const {
	for (auto room : rooms)
		if (room->isFree(date))
			std::cout << room->getNumber() << " with capacity " << room->getCapacity() << std::endl;
}

void Hotel::makeReservation(int roomNumber, Date* start, Date* end, std::string& note, int guests) {
	auto room = getRoom(roomNumber);
	if (room.has_value()) {
		guests = (guests == -1) ? room.value()->getCapacity() : guests;
		room.value()->reserve(start, end, note, guests);
	}
}

void  Hotel::emptyRoom(int roomNumber) {
	auto room = getRoom(roomNumber);
	if (room.has_value())
		room.value()->free();
}

void  Hotel::report(Date* start, Date* end) const {
	for (auto room : rooms) {
		int daysInUse = room->countDaysInUse(start, end);
		if (daysInUse > 0)
			std::cout << room->getNumber() << " used for " << daysInUse << " days" << std::endl;
	}
}

std::optional<int> Hotel::findAvailabeRoom(int beds, Date* start, Date* end) const {
	int numberBestRoom = -1, minCapacity = INT_MAX;
	for (auto room : rooms) {
		int capacity = room->getCapacity();

		if (capacity >= beds && room->isFree(start, end))
			if (capacity < minCapacity) {
				minCapacity = capacity;
				numberBestRoom = room->getNumber();
			}
	}

	return numberBestRoom == -1 ? std::nullopt : std::optional(numberBestRoom);
}

void Hotel::printRoomActivities(int roomNumber) const {
	auto room = getRoom(roomNumber);

	if (room.has_value()) {
		auto reservation = room.value()->findReservation(Date::today());
		if (reservation.has_value())
			for (const std::string& activity : reservation.value()->getActivities())
				std::cout << activity << std::endl;
	}
}

void Hotel::subscribeRoom(int roomNumber, std::string& activity) {
	auto room = getRoom(roomNumber);
	if (room.has_value() && validateActivity(activity))
		room.value()->subscribe(activity);
}

void Hotel::printSubscribedRooms(const std::string& activity)  const {
	if (!validateActivity(activity))
		return;

	for (auto room : rooms) {
		auto reservation = room->findReservation(Date::today());

		if (reservation.has_value()) {
			const std::set < std::string > activities = reservation.value()->getActivities();
			if (activities.find(activity) != activities.end())
				std::cout << room->getNumber() << std::endl;
		}
	}
}

const std::set<std::string>& Hotel::getAllActivities() const {
	return activities;
}

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
	for (auto room : hotel.rooms)
		os << *room;

	return os;
}

bool Hotel::validateActivity(const std::string& activity) const {
	if (activities.find(activity) == activities.end()) {
		std::cout << activity << " is not a valid hotel activity!" << std::endl;
		return false;
	}

	return true;
}



