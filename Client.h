#ifndef CYBER_CAFE_TEST_REPO_CLIENT_H
#define CYBER_CAFE_TEST_REPO_CLIENT_H

#include "Cyber_cafe.h"
#include <string>
#include <utility>

namespace cafe {

    class Client {
        friend class Cyber_cafe;

        std::string name;
        std::pair<int32_t, cafe::Time> table = {0, Time()}; // pair: (table, start_time)

    public:
        explicit Client(std::string name_): name(std::move(name_)){};
        Client() = default;
    };

}
#endif //CYBER_CAFE_TEST_REPO_CLIENT_H
