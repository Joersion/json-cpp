cmake_minimum_required(VERSION 3.12)
project(json-cpp)

ADD_DEFINITIONS( -O3 )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_PREFIX_PATH "~/work/poco")

find_package(Poco REQUIRED COMPONENTS JSON)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(json-cpp ${SOURCES})

target_link_libraries(json-cpp PRIVATE Poco::JSON)
