#!/bin/bash

CC=gcc
LDFLAGS=`pkg-config --libs glew`
LDFLAGS="$LDFLAGS -lglut"


$CC -c src/main.c -o build/main.o
gcc build/main.o $LDFLAGS -o build/main