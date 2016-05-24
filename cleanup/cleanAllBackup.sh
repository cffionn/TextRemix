#!/bin/bash

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

rm $path/Makefile~
rm $path/src/*.C~
rm $path/src/#*.C#
rm $path/testFunctions/*.C~
rm $path/testFunctions/#*.C#
rm $path/include/*.h~
rm $path/include/#*.h#
rm $path/*.md~
rm $path/python/*.py~
rm $path/*.sh~
rm $path/cleanup/*.sh~
rm $path/bash/*.sh~

sh $path/cleanup/cleanDatabaseBackup.sh