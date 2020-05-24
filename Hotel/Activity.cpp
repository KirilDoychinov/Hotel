#include "Activity.h"

std::ostream& operator<<(std::ostream& os, const Activity& a) {
	switch (a) {
	case Activity::TENNIS: os << "tennis";    break;
	case Activity::YOGA: os << "yoga"; break;
	case Activity::VOLLEYBALL: os << "volleyball";  break;
	case Activity::FOOTBALL: os << "football";   break;
	default: os.setstate(std::ios_base::failbit);
	}

	return os;
}
