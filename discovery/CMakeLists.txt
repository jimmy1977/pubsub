cmake_minimum_required(VERSION 3.0.2)

project (discovery)
find_package (Threads REQUIRED)
#find_package(pybind11 REQUIRED)
#find_package(PythonInterp REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3 -fPIC")
add_definitions(${GCC_COMPILE_FLAGS})

#set(UTIL_DIR ${PROJECT_SOURCE_DIR}/../../util)
#set(UTIL_LIB ${CMAKE_BINARY_DIR}/util/libutil.a)

#include_directories(${PROJECT_SOURCE_DIR}/../include/)
#include_directories(${CMAKE_BINARY_DIR}/src/)
#include_directories(${CMAKE_BINARY_DIR}//discovery/)
#include_directories(${PROJECT_SOURCE_DIR}/../../common/)
#include_directories(${PYTHON_INCLUDE_DIR})
#include_directories(${UTIL_DIR}/include)

set (COMMON_SOURCES ../../../../common/log.c)
#set (SERVER_SOURCES ../src/network_manager.cpp ../src/socket_helper.cpp)

if (${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
    add_compile_options(-O0 -g)
    add_definitions( -D_DEBUG )
else()
    add_compile_options(-O3)
endif()

# yaml-cpp
#set(YAMLCPP_VER 0.6.3)
#set(YAML_DIR ${PROJECT_SOURCE_DIR}/../../third_party/yamlcpp/${YAMLCPP_VER})
#include_directories("${YAML_DIR}/include")
#LINK_DIRECTORIES("${YAML_DIR}/lib/")

# Include directories
include_directories(${NANOPB_INCLUDE_DIRS})
include_directories("../../../common/")
include_directories(${CMAKE_BINARY_DIR}/server/src)
include_directories(${CMAKE_BINARY_DIR}/generated/)
include_directories(${CMAKE_BINARY_DIR}/generated/native)

# statsd
#set(STATSD_DIR ${PROJECT_SOURCE_DIR}/../../third_party/statsd/)
#include_directories("${STATSD_DIR}/")
#file(GLOB STATS_SOURCES "${STATSD_DIR}/*.cpp")

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
#message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")

#foreach(dir ${dirs})
#  message(STATUS "dir='${dir}'")
#endforeach()

#statsd
#include_directories(${PROJECT_SOURCE_DIR}/../../third_party/statsd/)

# crow and Boost
# find_package (Threads REQUIRED)
#SET(BOOST_VER 1.75.0)
#SET(BOOST_DIR ${PROJECT_SOURCE_DIR}/../../third_party/boost/${BOOST_VER})
#SET(CROW_DIR ${PROJECT_SOURCE_DIR}/../../third_party/crow)
#INCLUDE_DIRECTORIES("${CROW_DIR}/include")
#INCLUDE_DIRECTORIES("${BOOST_DIR}/include")
#LINK_DIRECTORIES("${BOOST_DIR}/lib")

# Util
#set(UTIL_DIR  ${PROJECT_SOURCE_DIR}/../../util)
#set(UTIL_LIB  ${CMAKE_BINARY_DIR}/util/libutil.a)
#include_directories(${UTIL_DIR}/include)

add_executable (discovery discovery.cpp) # TODO include other files as needed discovery_connection.cpp discovery_connection_factory.cpp ${SERVER_SOURCES} ${COMMON_SOURCES} ${STATS_SOURCES})
add_dependencies(discovery protogen_nat) # TODO add util as needed  util)
target_link_libraries(discovery protogen_nat ${CMAKE_THREAD_LIBS_INIT}) # TODO - add as needed ${UTIL_LIB} ${CMAKE_THREAD_LIBS_INIT} yaml-cpp)

add_custom_command(TARGET discovery POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/server/discovery/discovery_server ${CMAKE_BINARY_DIR}/bin/discovery)