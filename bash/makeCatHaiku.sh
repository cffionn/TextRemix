#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage: ./makeCatHaiku.sh <inputFile>"
    exit 1
fi


TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

dotTxt="."
haikuDotTxt="_Haiku.txt"

newFile=$1
rest2=${newFile#*$dotTxt}
pos2=$(( ${#newFile} - ${#rest2} ))
newFile=${newFile:0:$pos2-1}

exec="$path/bin/createHaiku.exe"
infile="$path/$1"
newFile2="$path/$newFile$haikuDotTxt"

$exec $infile
cat $newFile2