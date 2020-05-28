#include "Activity.h"
#include <algorithm>

Activity::Activity(std::string& activity) : activity(activity) {
}

Activity::Activity(const Activity& other) : activity(other.activity) {
}

Activity::~Activity() {
}

const std::string& Activity::getActivity() const {
	return activity;
}

 void Activity::printAllActivities()  {
	 for (const std::string& activity : activities)
		 std::cout << activity << std::endl;
}

Activity& Activity::operator=(Activity other) {
	swap(*this, other);
	return *this;
}

bool  operator==(const Activity& lhs, const Activity& rhs) {
	return lhs.activity == rhs.activity;
}

bool  operator<(const Activity& lhs, const Activity& rhs) {
	return lhs.activity < rhs.activity;
}

bool  operator!=(const Activity& lhs, const Activity& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Activity& activity) {
	os << activity.activity;
	return os;
}

void swap(Activity& first, Activity& second) {
	std::swap(first.activity, second.activity);
}
