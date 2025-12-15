cmake_minimum_required(VERSION 3.10)
project(MSHNew)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(MSHNew
    main.cpp
    src/System.cpp
    src/Logger.cpp
    src/SecuritySystem.cpp
    src/DetectionSystem.cpp
)
