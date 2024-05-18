#ifndef CYBER_CAFE_TEST_REPO_TIME_H
#define CYBER_CAFE_TEST_REPO_TIME_H

#include <cstdint>
#include <string>
#include <sstream>

namespace cafe {

    struct Time {
        int8_t hours;
        int8_t minutes;

        Time(int8_t hours_, int8_t minutes_) : hours(hours_), minutes(minutes_) {}

        Time() : hours(0), minutes(0) {};

        [[nodiscard]] std::string toString() const {
            std::stringstream ss;
            std::string del = ":";
            std::string hour_null;
            if (minutes < 10) {
                del += "0";
            }
            if (hours < 10) {
                hour_null = '0';
            }
            ss << hour_null << static_cast<int>(hours) << del << static_cast<int>(minutes);

            std::string ans = ss.str();
            return ss.str();
        }

        Time operator-(const Time &t2) const {
            int t1_minutes = hours * 60 + minutes;
            int t2_minutes = t2.hours * 60 + t2.minutes;
            int diff_minutes = abs(t2_minutes - t1_minutes);
            auto diff_hours = static_cast<int8_t>(diff_minutes / 60);
            auto diff_minutes_remainder = static_cast<int8_t>(diff_minutes % 60);
            return {diff_hours, diff_minutes_remainder};
        }

        Time &operator+=(const Time &t2) {
            minutes = static_cast<int8_t>(minutes + t2.minutes);
            hours = static_cast<int8_t>(hours + t2.hours);
            hours = static_cast<int8_t>(hours + minutes / 60);
            minutes %= 60;
            return *this;

        }

        bool operator<(const Time &other) const;
    };

}

#endif //CYBER_CAFE_TEST_REPO_TIME_H
