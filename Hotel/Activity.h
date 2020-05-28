#ifndef ACTIVITY_H
#define ACTIVITY_H

#include<iostream>
#include<fstream>
#include<set>

class Activity
{
public:
	Activity(std::string& activity);
	Activity(const Activity& other);
	~Activity();

	Activity& operator=(Activity other);

	const std::string& getActivity() const;
	static void printAllActivities();

	friend std::ostream& operator<<(std::ostream& os, const Activity& activity);
	friend void swap(Activity& first, Activity& second);
	friend bool  operator==(const Activity& lhs, const Activity& rhs);
	friend bool  operator!=(const Activity& lhs, const Activity& rhs);
	friend bool  operator<(const Activity& lhs, const Activity& rhs);

private:
	std::string activity;

	inline static std::set <std::string > allActivities = {
	   "football", "volleyball", "basketball", "tennis", "yoga", "swimming", "squash"
	};
};

#endif

