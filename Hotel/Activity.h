#ifndef ACTIVITY_H
#define ACTIVITY_H

#include<iostream>
#include<fstream>

enum class Activity : int
{
	FOOTBALL = 0,
	SWIMMING,
	VOLLEYBALL,
	TENNIS,
	YOGA,
	SQUASH,
	COUNT
};

std::ostream& operator<<(std::ostream& os, Activity activity);

#endif

