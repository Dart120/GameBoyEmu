
include(FetchContent)
file(GLOB SOURCES "src/*.cpp")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
add_executable(u_test test.cpp)

target_link_libraries(u_test
 PRIVATE
  GTest::GTest)

add_test(gtests u_test)