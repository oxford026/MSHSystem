cmake_minimum_required(VERSION 3.10)

project(MSHSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules/devices)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/state)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ModeSubsystem_Bashir)

add_subdirectory(modules/devices)

add_executable(MSHSystem
    main.cpp
    MSHSystem.cpp
    state/NormalState.cpp
    state/SleepState.cpp
    state/HighPerformanceState.cpp
    alarmsystem.cpp
    securitysystem.cpp
)

target_include_directories(MSHSystem PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/modules/devices
    ${CMAKE_CURRENT_SOURCE_DIR}/state
    ${CMAKE_CURRENT_SOURCE_DIR}/ModeSubsystem_Bashir
)

target_link_libraries(MSHSystem PRIVATE devices)

# Windows settings (if using conio.h) / إعدادات الويندوز (إذا كنت تستخدم conio.h)
if(WIN32)
    target_compile_definitions(MSHSystem PRIVATE _CONSOLE)
endif()

# Add thread library
find_package(Threads REQUIRED)
target_link_libraries(MSHSystem PRIVATE Threads::Threads)