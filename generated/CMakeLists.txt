
# Build the proto messages 
# We build for both x86 and arm 
cmake_minimum_required(VERSION 3.0.2)
project(protgen)
if((${ARCH} STREQUAL "x86_64"))
    add_subdirectory(native)
    #add_subdirectory(arm)
else()
    add_subdirectory(native)
endif()