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

	void addRoom(Room*);
	Room* findRoom(int);
	void addReservation(int, Reservation*);
	void availability(const Date& );
	void checkout(int);
	void report(const Date& , const Date& );
	int findRoom(int, const Date&, const Date&);
	void printRoomActivities(int);
	void printAllSubscribedFor(Activity&)



	friend std::ostream& operator<<(std::ostream&, const Hotel&);

private:
	std::vector<Room*> rooms;
};

#endif

