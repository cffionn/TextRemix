#!/bin/bash


TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

dotTxt="."
poemDotTxt="_SimplePoem.txt"

newFile=$1
rest2=${newFile#*$dotTxt}
pos2=$(( ${#newFile} - ${#rest2} ))
newFile=${newFile:0:$pos2-1}

exec="$path/bin/createSimplePoem.exe"
infile="$path/$1"
newFile2="$path/$newFile$poemDotTxt"

$exec $infile
cat $newFile2