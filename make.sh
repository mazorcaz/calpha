#!/bin/sh
# make.sh for calpha

mkdir -p bin/
tcc -g src/*.c -lm -lX11 -lGL -o bin/calpha
