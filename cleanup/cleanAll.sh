#!/bin/bash                                                                                                            

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

sh $path/cleanup/cleanAllBackup.sh
sh $path/cleanup/cleanExecutables.sh
sh $path/cleanup/cleanOutput.sh