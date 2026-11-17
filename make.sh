#!/bin/sh
# make.sh for calpha

mkdir -p bin/
tcc src/*.c -lX11 -lGL -o bin/calpha
