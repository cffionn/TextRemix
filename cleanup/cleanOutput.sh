#!/bin/bash                                                                                                            

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

rm $path/outputFull/*.txt
rm $path/outputTweet/*.txt
rm $path/outputSylSort/*.txt

rm $path/outputFull/*.txt~
rm $path/outputTweet/*.txt~
rm $path/outputSylSort/*.txt~

rm $path/outputFull/#*.txt#
rm $path/outputTweet/#*.txt#
rm $path/outputSylSort/#*.txt#

rmdir $path/outputFull
rmdir $path/outputTweet
rmdir $path/outputSylSort
