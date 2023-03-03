#!/bin/bash

make clean
make

echo "======= Encode ========"
./encode -i input.txt -o encoded.txt -v

echo "======= Decode ========"
./decode -i encoded.txt -o decoded.txt -v



make clean

