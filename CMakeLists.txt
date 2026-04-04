cmake_minimum_required(VERSION 3.16)
project(FIRST_CameraControl)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# CONFIG: use Boost's installed CMake package. Do not request COMPONENTS system:
# Boost.System is header-only since 1.69; Homebrew Boost no longer ships boost_system-* CMake configs.
find_package(Boost CONFIG REQUIRED)

find_package(Threads REQUIRED)

find_package(yaml-cpp REQUIRED)
include_directories(SYSTEM ${YAML_CPP_INCLUDE_DIRS})

include(FindPkgConfig)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

set(SOURCE_FILES
        src/main.cpp
        src/Joystick.cpp
        src/Controller.cpp
        src/Camera.cpp
        src/Configuration.cpp)

add_executable(FIRST_CameraControl ${SOURCE_FILES})
target_link_libraries(FIRST_CameraControl PRIVATE
        PkgConfig::SDL2
        Boost::headers
        Threads::Threads
        ${YAML_CPP_LIBRARIES})

add_custom_command(TARGET FIRST_CameraControl PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/config.yaml $<TARGET_FILE_DIR:FIRST_CameraControl>/config.yaml)
