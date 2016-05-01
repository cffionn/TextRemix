#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Usage: ./compile.sh <inputFile>"
    exit 1
fi

g++ $1 -Werror -Wall -O2 -o "${1/%.C/}.exe"