# Set the minimum version of cmake required 
cmake_minimum_required(VERSION 3.0.2)

# Set a project name 
project(pubsub)

# By default we build with RELEASE flag - else build with DEBUG 
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type was not set --- forcing it to DEBUG")
    set(CMAKE_BUILD_TYPE DEBUG)
endif()

# Fill in the version.h.in 
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

execute_process(
  COMMAND git rev-list --count HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_TAG_COUNT
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE
  )

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCH )
message(STATUS "Architecture : ${ARCH}")
# TODO - install gcc compiler for arm - then we can enable the ARM build
i# if((${ARCH} STREQUAL "x86_64") OR (${ARCH} STREQUAL "armv7l"))
if((${ARCH} STREQUAL "x86_64"))
    message(STATUS "Building for ${ARCH}")
else()
    message(FATAL_ERROR "Cannot build for  : ${ARCH}")
endif()

# Set global compile flags in one place
SET(GCC_COMPILE_FLAGS "-Wall -Werror")

# Create bin directory for copying all the binaries
execute_process(COMMAND mkdir bin)

# Copy version.h to the appropriate build directory 
configure_file(${CMAKE_SOURCE_DIR}/version/version.h.in ${CMAKE_BINARY_DIR}/generated/version.h)

 # Include the generated directory as part of each build 
 add_subdirectory(generated)

