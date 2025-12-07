#!/bin/bash

# Set the output binary name
OUTPUT="FRS"

# Set the source files
SOURCES="main.cpp src/DataStructures.cpp"

# Set the include directory
INCLUDE_DIR="-Iinclude"

# Compile the project
echo "Compiling the project..."
g++ $SOURCES $INCLUDE_DIR -o $OUTPUT $LIBRARIES

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable created: $OUTPUT"
else
    echo "Compilation failed!"
fi