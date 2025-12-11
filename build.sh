#!/usr/bin/env bash

echo "Compiling MSHSystem..."
g++ main.cpp MSHSystem.cpp -std=c++17 -o MSHSystem

if [ $? -eq 0 ]; then
  echo "Build successful. Run it with: ./MSHSystem"
else
  echo "Build failed."
fi
