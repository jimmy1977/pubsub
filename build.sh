#!/bin/bash 

#echo "Building Debug Binaries"


echo "Building Release Binaries"
rm -rf build/release && mkdir -p build/release && chmod 777 build && chmod 777 build/released
cd build/release 
cmake -DCMAKE_BUILD_TYPE=RELEASE ../..
make -j$(grep -c ^processor /proc/cpuinfo) all
