#!/bin/bash

set -e

if [ -d "build" ]; then
    echo "Removing existing build directory..."
    rm -rf build
fi

echo "Create build directory..."
mkdir -p build

cd build

echo "Start CMake"

cmake ..

cmake --build .

./PENISYUIPIZDA228AGAAGA
