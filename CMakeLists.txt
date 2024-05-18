cmake_minimum_required(VERSION 3.22)
project(cyber_cafe_test_repo)

set(CMAKE_CXX_STANDARD 20)

add_executable(cyber_cafe
        main.cpp
        Cyber_cafe.cpp
        Time.cpp
)

add_compile_options(-fsanitize=address)
add_compile_options(-fsanitize=undefined)

