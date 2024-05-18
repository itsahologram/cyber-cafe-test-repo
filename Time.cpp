#include "Time.h"


bool cafe::Time::operator<(const Time &other) const {
    if (hours < other.hours) {
        return true;
    } else if (hours == other.hours) {
        return minutes < other.minutes;
    } else {
        return false;
    }
}

