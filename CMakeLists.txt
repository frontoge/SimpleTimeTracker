cmake_minimum_required(VERSION 3.10)
project(SimpleTimeTracker)

set(CMAKE_CXX_Compiler "g++")

find_package(boost_serialization CONFIG REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(SimpleTimeTracker ${SOURCES})

target_link_libraries(SimpleTimeTracker PRIVATE Boost::serialization)
target_include_directories(SimpleTimeTracker PRIVATE include)