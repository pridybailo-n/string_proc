cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_compile_options(-std=c++17)
add_executable(run.out task.cpp)
target_link_libraries(run.out ${GTEST_LIBRARIES} pthread)