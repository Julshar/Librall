#!/bin/bash

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then # if build directory not exist
  echo "No build directory. Want to build project? [y/n]"
  read -r answer
  if [[ "$answer" == "y" || "$answer" == "Y" ]]; then
    ./makerun.sh
  else
    echo "Exiting without building."
    exit 0
  fi
fi

echo "Running Librall..."
cd "$BUILD_DIR"
./librall
cd ..

exit 0