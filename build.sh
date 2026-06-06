#!/bin/bash

g++ main.cpp -o ascii.exe \
    -std=c++11 \
    $(pkg-config --cflags --libs opencv4)

if [ $? -eq 0 ]; then
    ./ascii.exe
else
    echo "Compilation failed!"
fi