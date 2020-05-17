#include "Room.h"

Room::Room(int number, int capacity) : number(number), capacity(capacity), reservations(std::vector<Reservation*>()) {
}

Room::~Room() {
}

void reserve(tm start, tm end, std::string note, int numberOfGuests);

bool isFree(tm date);

bool isFree(tm start, tm end);

void free();

int countDaysInUse(tm start, tm end);
