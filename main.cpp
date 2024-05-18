#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

#include "Cyber_cafe.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " input_file";
        return 1;
    }

    std::string input_file = argv[1];

    std::ifstream file(input_file);
    if (!file.is_open()) {
        std::cout << "Error opening file " << input_file;
        return 1;
    }

    int32_t tables, start_hours, start_min, end_hours, end_min, price;
    std::string line;
    try {
        std::getline(file, line);
        tables = std::stoi(line);

        std::getline(file, line);
        sscanf(line.c_str(), "%d:%d %d:%d", &start_hours, &start_min, &end_hours, &end_min);
        if (std::min({start_hours, start_min, end_hours, end_min}) < 0 ||
            std::max({start_hours, end_hours}) > 23 ||
            std::max(start_min, end_min) > 59) {
            throw std::runtime_error("Input error");
        }

        std::getline(file, line);
        price = std::stoi(line);
    } catch (std::exception &e) {
        std::cout << line;
        return 1;
    }

    cafe::Cyber_cafe cafe = cafe::Cyber_cafe(tables,
                                             cafe::Time(static_cast<int8_t>(start_hours),
                                                        static_cast<int8_t>(start_min)),
                                             cafe::Time(static_cast<int8_t>(end_hours), static_cast<int8_t>(end_min)),
                                             price);


    cafe::Time prev_time = cafe::Time();
    while (std::getline(file, line)) {
        try {
            std::stringstream ss(line);

            std::string time_string, id;
            ss >> time_string >> id;

            sscanf(line.c_str(), "%d:%d", &start_hours, &start_min);
            if (std::min({start_hours, start_min}) < 0 ||
                start_hours > 23 || start_min > 59) {
                throw std::runtime_error("Input error");
            }
            cafe::Time time = cafe::Time(static_cast<int8_t>(start_hours),
                                         static_cast<int8_t>(start_min));

            if (time < prev_time) {
                throw std::runtime_error("Input error");
            }
            prev_time = time;
            int32_t cmd_id = 0;
            cmd_id = std::stoi(id);

            switch (cmd_id) {
                case 1: {
                    std::string name;
                    ss >> name;
                    std::cout << line << '\n';
                    cafe.ID1_client_came(time, name);
                    break;
                }
                case 2: {
                    std::string name;
                    int32_t table;
                    ss >> name >> table;
                    std::cout << line << '\n';
                    cafe.ID2_client_seat(time, name, table);
                    break;
                }
                case 3: {
                    std::string name;
                    ss >> name;
                    std::cout << line << '\n';
                    cafe.ID3_client_wait(name, time);
                    break;
                }
                case 4: {
                    std::string name;
                    ss >> name;
                    std::cout << line << '\n';
                    cafe.ID_4_client_left(name, time);
                    break;
                }
                default: {
                    throw std::runtime_error("Input error");
                }
            }
            int b = 10;
        }
        catch (cafe::Cyber_Cafe_Exception &ex) {
            cafe::Cyber_cafe::ID13_error(ex);
            std::cout << '\n';
        } catch (std::exception &ex) {
            std::cout << line << '\n';
            return 1;
        }
    }
    cafe.close_and_print();
    file.close();
}
