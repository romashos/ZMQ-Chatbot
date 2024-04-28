cmake_minimum_required(VERSION 3.0)
project(ZMQExamples)

# Set the path to the vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Add the installation prefix of ZeroMQ
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-windows)

# Find the ZeroMQ package
find_package(ZeroMQ CONFIG REQUIRED)

# Define your executables
add_executable(requester requester.c)
add_executable(responder responder.c)

find_library(ZMQ_LIBRARY NAMES libzmq zmq HINTS "${PROJECT_SOURCE_DIR}/../include")
find_library(ZMQ_LIBRARY NAMES libzmq-mt-4_3_5 HINTS "${PROJECT_SOURCE_DIR}/vcpkg/installed/x64-windows/lib")

target_link_libraries(requester PRIVATE libzmq libzmq-mt-4_3_5)
target_link_libraries(responder PRIVATE libzmq libzmq-mt-4_3_5)
target_include_directories(requester PRIVATE ${PROJECT_SOURCE_DIR}/include)