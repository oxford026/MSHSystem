cmake_minimum_required(VERSION 3.10)

project(MSHSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(modules/devices)

add_executable(MSHSystem
    main.cpp
    MSHSystem.cpp
)

target_link_libraries(MSHSystem PRIVATE devices)
