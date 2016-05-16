#!/bin/bash
if [ $# -ne 1 ]
then
    echo "Usage: ./compile.sh <inputFile>"
    exit 1
fi

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

srcStr="src/"
output=${1#*$srcStr}

g++ $1 -Werror -Wall -Wextra -I $path -O2 -o "bin/${output/%.C/}.exe"