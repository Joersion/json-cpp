cmake_minimum_required(VERSION 3.12)
project(jsonTest)

ADD_DEFINITIONS( -O3 )

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "~/work/poco")

find_package(Poco REQUIRED COMPONENTS JSON)

add_executable(jsonTest test.cpp)

target_link_directories(jsonTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../build/ )

target_link_libraries(jsonTest PRIVATE json Poco::JSON)
