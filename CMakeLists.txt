# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(test)


find_package(fmt CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE fmt::fmt)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)