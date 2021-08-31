cmake_minimum_required(VERSION 3.16)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/../CCSDSlib" "${CMAKE_SOURCE_DIR}/../CCSDSlib/include")
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread ${CMAKE_SOURCE_DIR}/../CCSDSlib/libCCSDS.so)

