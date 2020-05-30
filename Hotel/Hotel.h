#ifndef HOTEL_H
#define HOTEL_H

#include"Room.h"
#include<vector>
#include<string>
#include <optional>

/**
 * @class  Hotel
 *
 * @brief  Class representing an hotel enity with  list of hotel rooms
 * 		   and list of available sport activities
 *
 */

class Hotel
{
public:
	Hotel();
	~Hotel();

	void addRoom(int number, int capacity);
	std::optional<Room*> getRoom(int roomNumber) const;

	void makeReservation(int room, Date* start, Date* end, std::string& note, int guests = -1);
	void emptyRoom(int room);

	bool hasRooms() const;
	bool hasRoom(int number) const;

	void printAvailableRooms(Date* date) const;
	void printRoomsUsage(Date* start, Date* end) const;
	std::optional<int> findAvailabeRoom(int beds, Date* start, Date* end) const;
	void printRoomActivities(int room) const;
	void printSubscribedRooms(const std::string& activity) const;
	void subscribeRoom(int room, std::string& activity);

	const std::set<std::string>& getAllActivities() const;

	friend std::ostream& operator<<(std::ostream&, const Hotel&);

private:
	
	/**
	 * List of existing hotel rooms
	 */
	std::vector<Room*> rooms;

	/**
	 * List of existing hotel activities
	 */
	const std::set <std::string> activities = { "football", "golf","yoga","swimming","volleyball","squash", "tennis" };

	Room* findRoom(int roomNumber) const;
	bool hasActivity(const std::string& activity) const;
};

#endif