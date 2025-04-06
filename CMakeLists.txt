cmake_minimum_required(VERSION 3.10)
project(SimpleTimeTracker)

set(CMAKE_CXX_Compiler "g++")

find_package(boost_serialization CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB SOURCES "src/*.cpp")
file(GLOB NESTED_SOURCES "src/add_deps/*.cpp")
add_executable(SimpleTimeTracker ${SOURCES} ${NESTED_SOURCES})

target_link_libraries(SimpleTimeTracker PRIVATE Boost::serialization)
target_link_libraries(SimpleTimeTracker PRIVATE imgui::imgui)
target_link_libraries(SimpleTimeTracker PRIVATE glfw)
target_link_libraries(SimpleTimeTracker PRIVATE GLEW::GLEW)

target_include_directories(SimpleTimeTracker PRIVATE include)
target_include_directories(SimpleTimeTracker PRIVATE include/add_deps)