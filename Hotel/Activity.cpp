#include "Activity.h"

std::ostream& operator<<(std::ostream& os, Activity activity) {
	switch (activity)
	{
	case Activity::FOOTBALL: os << "football";    break;
	case Activity::SWIMMING: os << "swimming"; break;
	case Activity::VOLLEYBALL: os << "volleyball";  break;
	case Activity::TENNIS: os << "tennis";   break;
	case Activity::YOGA: os << "yoga";   break;
	case Activity::SQUASH: os << "squash";   break;
	default: os << "unknown";
	}
	return os;
}
