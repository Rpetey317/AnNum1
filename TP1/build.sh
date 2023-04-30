#! /bin/bash

FILES=`echo ./src/*.c main.c`
CFLAGS=`echo -g -std=c17`
OUTNAME=main

gcc "$CFLAGS" "$FILES" -o $OUTNAME -lm