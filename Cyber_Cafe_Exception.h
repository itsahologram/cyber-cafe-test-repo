#ifndef CYBER_CAFE_TEST_REPO_CYBER_CAFE_EXCEPTION_H
#define CYBER_CAFE_TEST_REPO_CYBER_CAFE_EXCEPTION_H

#include <stdexcept>

namespace cafe {

    struct Cyber_Cafe_Exception : public std::runtime_error {
        explicit Cyber_Cafe_Exception(cafe::Time time, const std::string &message)
                : std::runtime_error(time.toString() + " 13 " + message) {};
    };

    struct YouShallNotPass : public Cyber_Cafe_Exception {
        explicit YouShallNotPass(cafe::Time time) : Cyber_Cafe_Exception(time, "YouShallNotPass") {};
    };

    struct NotOpenYet : public Cyber_Cafe_Exception {
        explicit NotOpenYet(cafe::Time time) : Cyber_Cafe_Exception(time, "NotOpenYet") {};
    };

    struct PlaceIsBusy : public Cyber_Cafe_Exception {
        explicit PlaceIsBusy(cafe::Time time) : Cyber_Cafe_Exception(time, "PlaceIsBusy") {};
    };

    struct ClientUnknown : public Cyber_Cafe_Exception {
        explicit ClientUnknown(cafe::Time time) : Cyber_Cafe_Exception(time, "ClientUnknown") {};
    };

    struct ICanWaitNoLonger : public Cyber_Cafe_Exception {
        explicit ICanWaitNoLonger(cafe::Time time) : Cyber_Cafe_Exception(time, "ICanWaitNoLonger!") {};
    };
}

#endif //CYBER_CAFE_TEST_REPO_CYBER_CAFE_EXCEPTION_H
