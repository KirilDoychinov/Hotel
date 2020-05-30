#include "Hotel.h"
#include "Room.h"
#include <iostream>
#include <optional>

/**
 * @brief	Default constructor creating empty hotel with no rooms
 *
 */

Hotel::Hotel() : rooms(std::vector<Room*>()) {
}

/**
 * @brief	Destructs the hotel deallocating dynamic memory
 *
 */

Hotel::~Hotel() {
	for (auto room : rooms) {
		delete room;
	}
}

/**
 * @brief	 Gets all hotel activities
 *
 * @returns	 All hotel activities
 * 			
 */

const std::set<std::string>& Hotel::getAllActivities() const {
    return activities;
}

/**
 * @brief	 Check if hotel has any rooms
 *
 * @returns	 True if the hotel has any rooms, false if not
 */

bool Hotel::hasRooms() const {
	return !rooms.size() == 0;
}

/**
 * @brief				Check if hotel has room with given number
 *
 * @param [in] 	number	Number of room
 *
 * @returns				True if the hotel has room with this number, false if not
 */

bool Hotel::hasRoom(int number) const {
	return findRoom(number) != nullptr;
}

/**
 * @brief				    Get a room by room number
 *
 * @param [in]	roomNumber	The room number
 *
 * @returns				    The room with this number, or empty value otherwise
 */

std::optional<Room*> Hotel::getRoom(int roomNumber) const {
	auto room = findRoom(roomNumber);
	if (room == nullptr) {
		std::cout << "Room with number " << roomNumber << " does not exist!" << std::endl;
		return {};
	}
	return room;
}

/**
 * @brief					Creates a hotel room with the given number and capacity
 *
 * @param [in] 	roomNumber	The number of the room
 * 				
 * @param [in] 	capacity  	The room capacity
 * 				
 */

void Hotel::addRoom(int roomNumber, int capacity) {
	if (!hasRoom(roomNumber)) {
		std::cout << "Room " << roomNumber << " was succesfully read!" << std::endl;
		rooms.push_back(new Room(roomNumber, capacity));
	}
	else
		std::cout << "Error with room " << roomNumber << "! Room is already present in the system!" << std::endl;
}

/**
 * @brief				    Finds a room by room number
 *
 * @param [in]	roomNumber	The room number
 *
 * @returns				    The room with this number, or nullptr otherwise
 */

Room* Hotel::findRoom(int roomNumber) const {
	for (auto room : rooms)
		if (room->getNumber() == roomNumber)
			return room;

	return nullptr;
}

/**
 * @brief				Print all rooms available on given date and alert
 * 						if none is present
 *
 * @param [in]	date	Date
 *
 */

void Hotel::printAvailableRooms(Date* date) const {
	bool foundAvailableRooms = false;

	for (auto room : rooms)
		if (room->isFree(date)) {
			std::cout << room->getNumber() << " with capacity " << room->getCapacity() << std::endl;
			foundAvailableRooms = true;
		}

	if (!foundAvailableRooms)
		std::cout << "No available rooms were found for the given date!" << std::endl;
}

/**
 * @brief	Creates a reservation for the given room
 *
 * @param [in]  roomNumber	Room number
 * 					
 * @param [in]	start	  	Start date of reservation
 * 					
 * @param [in]	end		  	End date of reservation
 * 					
 * @param [in]	note	  	Note
 * 					
 * @param [in]	guests	  	Number of guests
 * 								
 */

void Hotel::makeReservation(int roomNumber, Date* start, Date* end, std::string& note, int guests) {
	auto room = getRoom(roomNumber);
	if (room.has_value()) {
		guests = (guests == -1) ? room.value()->getCapacity() : guests;
		room.value()->reserve(start, end, note, guests);
	}
}

/**
 * @brief	                Empty the room with the given number, 
 * 			                effectively removing any ongoing reservation
 *
 * @param [in]	roomNumber	Number of room
 */

void  Hotel::emptyRoom(int roomNumber) {
	auto room = getRoom(roomNumber);
	if (room.has_value())
		room.value()->free();
}

/**
 * @brief					Prints the days every hotel room was used in 
 * 							the given period of time
 *
 * @param [in]	start	  	Start date
 *
 * @param [in]	end		  	End date
 *
 */

void  Hotel::printRoomsUsage(Date* start, Date* end) const {
	for (auto room : rooms) {
		int daysInUse = room->countDaysInUse(start, end);
		if (daysInUse > 0)
			std::cout << room->getNumber() << " used for " << daysInUse << " days" << std::endl;
		else
			std::cout << room->getNumber() << " was not used in the given period!" << std::endl;
	}
}

/**
 * @brief				Searches for an available hotel room that can accomodate given
 * 						number of guests for given period
 *
 * @param [in]	beds 	Number of beds required
 * 							
 * @param [in]	start	Start date
 * 					
 * @param [in]	end  	End date
 *
 * @returns				A free hotel room with the minimum capacity able
 * 						 to accomodate the guests, or empty value otherwise
 * 			
 */

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

/**
 * @brief				     Prints all activites given room has subscribed
 *
 * @param [in]	roomNumber   Number of room
 *
 */

void Hotel::printRoomActivities(int roomNumber) const {
	auto room = getRoom(roomNumber);

	if (room.has_value()) {
		auto reservation = room.value()->findReservation(Date::today());
		if (reservation.has_value()) {
			auto activities = reservation.value()->getActivities();
			if (!activities.empty()) {
				for (const std::string& activity : activities)
					std::cout << activity << std::endl;
				return;
			}
		}
	}
	std::cout << "Room has not subscribed for any activites yet!" << std::endl;
}

/**
 * @brief				    Susbscribe given room for given activity
 *
 * @param [in]	roomNumber 	Number of room to be subscribed
 *
 * @param [in]	activity	Activity
 *
 */

void Hotel::subscribeRoom(int roomNumber, std::string& activity) {
	auto room = getRoom(roomNumber);
	if (room.has_value() && hasActivity(activity)) {
		room.value()->subscribe(activity);
	}
}

/**
 * @brief				    Prints all rooms subscribed for given activity
 *
 * @param [in]	activity	Activity
 *
 */

void Hotel::printSubscribedRooms(const std::string& activity)  const {
	if (!hasActivity(activity))
		return;

	int subscriptions = 0;

	for (auto room : rooms) {
		auto reservation = room->findReservation(Date::today());

		if (reservation.has_value()) {
			const std::set < std::string > activities = reservation.value()->getActivities();
			if (activities.find(activity) != activities.end()) {
				std::cout << room->getNumber() << std::endl;
				++subscriptions;
			}
		}
	}

	if (subscriptions == 0)
		std::cout << "No room has currently subscribed for " << activity << "!" << std::endl;
}

/**
 * @brief	               Stream insertion operator for Hotel objects
 *
 * @param [in,out]  os	   The output stream
 *
 * @param [in]	    hotel  Hotel to be streamed
 *
 * @returns	               The streamed hotel object
 *
 */

std::ostream& operator<<(std::ostream& os, const Hotel& hotel) {
	for (auto room : hotel.rooms)
		os << *room;

	return os;
}

/**
 * @brief	            Check if given acitivity exists
 *
 * @param 	activity	The activity.
 *
 * @returns	            True if activity is present, false otherwise
 */

bool Hotel::hasActivity(const std::string& activity) const {
	if (activities.find(activity) == activities.end()) {
		std::cout << activity << " is not a valid hotel activity!" << std::endl;
		return false;
	}
	return true;
}



