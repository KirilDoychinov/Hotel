#ifndef HOTEL_H
#define HOTEL_H

#include"Room.h"
#include<vector>
#include<string>
#include <optional>

class Hotel
{
public:
	Hotel();
	~Hotel();

	void addRoom(int number, int capacity);
	std::optional<Room*> getRoom(int roomNumber) const;

	void makeReservation(int room, Date* start, Date* end, std::string& note, int guests = -1);
	void emptyRoom(int room);

	bool isEmpty() const;
	bool hasRoom(int number) const;

	void printAvailableRooms(Date* date) const;
	void report(Date* start, Date* end) const;
	std::optional<int> findAvailabeRoom(int beds, Date* start, Date* end) const;
	void printRoomActivities(int room) const;
	void printSubscribedRooms(const std::string& activity) const;
	void subscribeRoom(int room, std::string& activity);

	const std::set<std::string>& getAllActivities() const;

	friend std::ostream& operator<<(std::ostream&, const Hotel&);

private:
	std::vector<Room*> rooms;
	const std::set <std::string> activities = { "football", "golf","yoga","swimming","volleyball","squash" };

	Room* findRoom(int number) const;
	bool validateActivity(const std::string& activity) const;
};

#endif