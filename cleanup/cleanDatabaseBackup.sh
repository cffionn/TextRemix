#!/bin/bash

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}


rm $path/inputDatabase/*.txt~
rm $path/rhymeDatabase/*.txt~
rm $path/syllableDatabase/*.txt~