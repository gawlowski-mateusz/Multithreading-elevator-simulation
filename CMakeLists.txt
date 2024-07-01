cmake_minimum_required(VERSION 3.28)
project(SO2_Elevator)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(SO2_Elevator
        Source/main.cpp
        Elevator/Elevator.cpp
        Elevator/Elevator.h
        Scene/Scene.cpp
        Scene/Scene.h
        Client/Client.cpp
        Client/Client.h
)

target_link_libraries(SO2_Elevator ${CURSES_LIBRARIES})
