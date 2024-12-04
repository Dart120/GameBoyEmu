cmake_minimum_required(VERSION 3.15)

# Project Name
project(gameboyemu)

# Define the top-level directory for source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Gather all `.cpp` files recursively
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

# Add the main executable
add_executable(main ${SRC_FILES})

# Include directories for Conan dependencies (automatically handled by the toolchain)
target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR})

# Link SDL2 libraries
find_package(SDL2 REQUIRED)
target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})

# Link spdlog libraries
find_package(spdlog REQUIRED)
target_link_libraries(main PRIVATE spdlog::spdlog)

# Link Conan libraries
target_link_libraries(main PRIVATE ${CONAN_LIBS})

