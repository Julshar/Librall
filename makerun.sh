#!/bin/bash         

set -e  # Exit on any error
echo "Building the project..."

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    echo "Removing previous build..."
    rm -rf "$BUILD_DIR"
else
    mkdir "$BUILD_DIR"
fi

echo "Running CMake..."
cmake -DCMAKE_BUILD_TYPE=Release -S src -B "$BUILD_DIR"

echo "Building..."
cmake --build "$BUILD_DIR" -- -j$(nproc)
# cmake --build BUILD_DIR
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build succeeded!"
echo "Copying data files..."
cp -r data "$BUILD_DIR"/data

echo "Running the project..."
cd "$BUILD_DIR"
./librall
cd ..

exit 0
