#ifndef HOTEL_H
#define HOTEL_H

#include"Room.h"
#include<vector>
#include<string>

class Hotel
{
public:
	Hotel();
	~Hotel();

	void addRoom(int number, int capacity);
	Room* findRoom(int number) const;

	void makeReservation(int room, Date* start, Date* end, std::string& note, int guests = -1);
	void emptyRoom(int room);

	bool empty() const;
	bool hasRoom(int room) const;
	void availability(Date* date) const;
	void report(Date* start, Date* end) const;
	int findRoom(int beds, Date* start, Date* end) const;
	void printRoomActivities(int room) const;
	//void printSubs(const Activity& activity) const;
	void addActivity(int room, std::string& activity);

	friend std::ostream& operator<<(std::ostream&, const Hotel&);

private:
	std::vector<Room*> rooms;
};

#endif

