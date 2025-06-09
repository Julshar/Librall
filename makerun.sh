#!/bin/bash         

echo "Building the project..."

DIR="build"

if [ -d "$DIR" ]; then
    echo "Removing previous build..."
    rm -rf "$DIR"/*
    rm -rf "$DIR"/.[!.]* "$DIR"/..?* 2>/dev/null # Removes hidden files/directories
else
    mkdir "$DIR"
fi

cmake -DCMAKE_BUILD_TYPE=Release -S src -B build
cmake --build build
if [ $? -ne 0 ]; then
    echo "Build failed!"
    exit 1
fi

echo "Build succeeded!"
echo "Running the project..."

./build/librall

exit 0
