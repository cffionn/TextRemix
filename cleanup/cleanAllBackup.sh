#!/bin/bash

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

rm $path/Makefile~
rm $path/*.C~
rm $path/#*.C#
rm $path/testFunctions/*.C~
rm $path/*.h~
rm $path/*.md~
rm $path/interface/*.h~
rm $path/*.sh~
rm $path/cleanup/*.sh~
rm $path/inputDatabase/*.txt~
rm $path/rhymeDatabase/*.txt~
rm $path/syllableDatabase/*.txt~