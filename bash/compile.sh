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

mkdir -p $path/bin


srcStr="src/"
output=${1#*$srcStr}

g++ $1 -Werror -Wall -Wextra -Wno-unused-local-typedefs -I $path -I /opt/local/include -O2 -o "$path/bin/${output/%.C/}.exe"