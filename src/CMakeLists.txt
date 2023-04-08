cmake_minimum_required(VERSION 2.4)

project(gameboyemu)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Specify the top-level directory containing the executables
set(EXECUTABLE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Use file globbing to generate a list of all executables in the directory and its subdirectories
file(GLOB_RECURSE EXECUTABLES ${EXECUTABLE_DIR}/*.cpp)

# Loop over the list of executables and call add_executable for each file
foreach(EXECUTABLE ${EXECUTABLES})
    get_filename_component(EXECUTABLE_NAME ${EXECUTABLE} NAME_WE)
    add_executable(main ${EXECUTABLE})
endforeach()



# add_executable (main main.cpp cpu.cpp memory.cpp LD/LD.cpp MATH/MATH.cpp INCDEC/INCDEC.cpp JUMP/JUMP.cpp LOGIC/LOGIC.cpp RETURNS/RETURNS.cpp POPPUSH/POPPUSH.cpp CALL/CALL.cpp RST/RST.cpp)
target_link_libraries(main ${CONAN_LIBS})
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
