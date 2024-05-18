#ifndef CYBER_CAFE_TEST_REPO_CYBER_CAFE_H
#define CYBER_CAFE_TEST_REPO_CYBER_CAFE_H

#include <cstdint>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <stdexcept>

#include "Time.h"
#include "Client.h"
#include "Cyber_Cafe_Exception.h"

namespace cafe {

    class Cyber_cafe {
    private:
        std::map<std::string, cafe::Client> clients_inside;
        std::queue<std::string> queue;
        std::vector<bool> is_occupied;
        std::vector<std::pair<int32_t, cafe::Time>> tables_revenue;

        void reserve_table(int32_t table, std::string &name, cafe::Time time);

        void remove_reserve_table(std::string &name, cafe::Time time);

        void ID_11_client_left(std::string &name, cafe::Time time, bool isFromID4);

        void ID12_client_seat(cafe::Time time, std::string &name, int32_t num);

    public:
        cafe::Time start_time;
        cafe::Time end_time;
        uint32_t cost;

        Cyber_cafe(int32_t count_, cafe::Time start_, cafe::Time end_,
                   uint32_t cost_) : start_time(start_), end_time(end_), cost(cost_) {
            tables_revenue.resize(count_ + 1);
            is_occupied.resize(count_ + 1);
            std::cout << start_.toString() << '\n';
        }

        void ID1_client_came(cafe::Time time, const std::string &name);

        void ID2_client_seat(cafe::Time time, const std::string &name, int32_t num);

        void ID3_client_wait(std::string &name, cafe::Time time);

        void ID_4_client_left(std::string &name, cafe::Time time);

        void close_and_print();

        static void ID13_error(const cafe::Cyber_Cafe_Exception &e);

    };
}
#endif //CYBER_CAFE_TEST_REPO_CYBER_CAFE_H
