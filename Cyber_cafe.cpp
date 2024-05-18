#include <iostream>
#include "Cyber_cafe.h"

void cafe::Cyber_cafe::ID1_client_came(cafe::Time time, const std::string &name) {
    if (clients_inside.contains(name)) {
        throw YouShallNotPass(time);
    }
    if (time < start_time) {
        throw NotOpenYet(time);
    }
    clients_inside[name] = Client(name);
    int a = 0;
}

void cafe::Cyber_cafe::ID2_client_seat(cafe::Time time, const std::string &name, int32_t num) {
    if (!clients_inside.contains(name)) {
        throw ClientUnknown(time);
    }
    if (is_occupied[num]) {
        throw PlaceIsBusy(time);
    }
    if (clients_inside[name].table.first != 0) {
        remove_reserve_table(const_cast<std::string &>(name), time);
    }
    reserve_table(num, const_cast<std::string &>(name), time);

}

void cafe::Cyber_cafe::ID3_client_wait(std::string &name, cafe::Time time) {
    if (std::find(is_occupied.begin() + 1, is_occupied.end(), false) != is_occupied.end()) {
        throw ICanWaitNoLonger(time);
    }
    if (queue.size() == is_occupied.size() - 1) {
        ID_11_client_left(name, time, false);
    }
    queue.push(name);
}

void cafe::Cyber_cafe::ID_11_client_left(std::string &name, cafe::Time time,
                                         bool isFromID4) {
    auto &client = clients_inside[name];
    if (client.table.first != 0) {
        int32_t table = client.table.first;
        remove_reserve_table(client.name, time);
        if (!queue.empty()) {
            auto queue_client = queue.front();
            ID12_client_seat(time, queue_client, table);
            queue.pop();
        }
    }
    if (!isFromID4) {
        std::cout << time.toString() << ' ' << 11 << ' ' << name << '\n';
    }
    clients_inside.erase(name);
}

void cafe::Cyber_cafe::ID_4_client_left(std::string &name, cafe::Time time) {
    if (!clients_inside.contains(name)) {
        throw ClientUnknown(time);
    }
    ID_11_client_left(name, time, true);
}

void cafe::Cyber_cafe::ID12_client_seat(cafe::Time time, std::string &name, int32_t num) {
    reserve_table(num, name, time);
    std::cout << time.toString() << ' ' << 12 << ' ' << name << ' ' << clients_inside[name].table.first << '\n';
}

void cafe::Cyber_cafe::ID13_error(const cafe::Cyber_Cafe_Exception &e) {
    std::cout << e.what();
}

void cafe::Cyber_cafe::remove_reserve_table(std::string &name, cafe::Time time) {
    auto &client = clients_inside[name];

    cafe::Time diff_time = time - client.table.second;
    int32_t paid_hours = diff_time.hours + ((diff_time.minutes != 0) ? 1 : 0);
    tables_revenue[client.table.first].first += cost * paid_hours;
    tables_revenue[client.table.first].second += diff_time;

    is_occupied[client.table.first] = false;
    client.table.first = 0;

}

void cafe::Cyber_cafe::reserve_table(int32_t table, std::string &name, cafe::Time time) {
    clients_inside[name].table = {table, time};
    is_occupied[table] = true;
}

void cafe::Cyber_cafe::close_and_print() {
    std::vector<std::string> names;
    names.reserve(clients_inside.size());
    for (auto const &[key, value]: clients_inside) {
        names.push_back(key);
    }
    std::sort(names.begin(), names.end());
    for (auto const &name: names) {
        ID_11_client_left(const_cast<std::string &>(name), end_time, false);
    }
    std::cout << end_time.toString() << '\n';

    for (int i = 1; i < tables_revenue.size(); ++i) {
        std::cout << i << ' ' << tables_revenue[i].first << ' ' << tables_revenue[i].second.toString() << '\n';
    }
}


