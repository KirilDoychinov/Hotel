#ifndef ACTIVITY_H
#define ACTIVITY_H

#include<iostream>
#include<fstream>

enum class Activity
{
	TENNIS,
	YOGA,
	VOLLEYBALL,
	FOOTBALL
};

std::ostream& operator<<(std::ostream&, const Activity&);

#endif

