# CMakeLists.txt
cmake_minimum_required(VERSION 3.0)
project(test)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
add_subdirectory(tests)

add_executable(main ${SOURCES})
target_link_libraries(main PRIVATE fmt::fmt)
target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)


add_test(multiply_gtests multiply_test)