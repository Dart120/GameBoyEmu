cmake_minimum_required(VERSION 2.4)

project(gameboyemu)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



add_executable (main main.cpp cpu.cpp memory.cpp LD/LD.cpp MATH/MATH.cpp INCDEC/INCDEC.cpp JUMP/JUMP.cpp LOGIC/LOGIC.cpp RETURNS/RETURNS.cpp POPPUSH/POPPUSH.cpp CALL/CALL.cpp)
target_link_libraries(main ${CONAN_LIBS})
# Link the executable to the Hello library. Since the Hello library has
# public include directories we will use those link directories when building
# helloDemo
