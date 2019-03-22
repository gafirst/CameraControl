cmake_minimum_required(VERSION 3.5.1)
project(FIRST_CameraControl)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

find_package(Boost REQUIRED COMPONENTS system)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

find_package (Threads)

find_package(yaml-cpp REQUIRED)
include_directories(SYSTEM ${YAML_CPP_INCLUDE_DIRS})

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES
        src/main.cpp
        src/Joystick.cpp
        src/Controller.cpp
        src/Camera.cpp
        src/Configuration.cpp)

add_executable(FIRST_CameraControl ${SOURCE_FILES})
target_link_libraries(FIRST_CameraControl ${SDL2_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${YAML_CPP_LIBRARIES})

add_custom_command(TARGET FIRST_CameraControl PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config.yaml $<TARGET_FILE_DIR:FIRST_CameraControl>/config.yaml)
