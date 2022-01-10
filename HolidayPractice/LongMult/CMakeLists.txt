#minimum required version must be included or you get a warning
cmake_minimum_required(VERSION 3.16)
#missing a project name gets you a warning
project(LongMult)

#locate GTest
find_package(GTest REQUIRED)
#these variables are defined inside of gtests directories, it's a cmake thing
include_directories(${GTEST_INCLUDE_DIRS}) 
string(APPEND CMAKE_CXX_FLAGS " -g -o0")
#Link runTests with Gtest and pthread libraries
#also remember any other cpp files the project uses
add_executable(LilMult LilMult.cpp BigNumber.cpp)
target_link_libraries(LilMult ${GTEST_LIBRARIES} pthread)
add_executable(runTests testMain.cpp BigNumber.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

