#!/bin/bash 

#echo "Building Debug Binaries"


echo "Building Release Binaries"
rm -rf build/release && mkdir build/release && chrmod 777 build/release
cd build/release 
cmake -DCMAKE_BUILD_TYPE=RELEASE ../..
make -j$(grep -c ^processor /proc/cpuinfo) all