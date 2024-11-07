#!/bin/bash

# Check if a C file name is provided
if [ -z "$1" ]; then    
    echo "Usage: ./compile.sh path/to/filename.c"
    exit 1
fi

# Extract directory and filename from the input path
filename=$(basename "$1" .c)         # Get the filename without extension
directory=$(dirname "$1")            # Get the directory path

# Create the output subdirectory structure
mkdir -p "output/$directory"

# Compile the C file and place the executable in the output subdirectory
gcc -g -Wall -Wextra -O2 -std=c99 "$1" -o "output/$directory/$filename"

# Check if the compilation succeeded
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable created: output/$directory/$filename"
    # Run the executable from the output directory
    "./output/$directory/$filename"
else
    echo "Compilation failed."
fi
