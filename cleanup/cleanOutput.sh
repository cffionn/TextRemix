#!/bin/bash                                                                                                            

TextRemix="TextRemix"
path=$PWD
rest=${path#*$TextRemix}
pos=$(( ${#path} - ${#rest} ))
path=${path:0:$pos}

rm $path/outputFull/*.txt
rm $path/outputTweet/*.txt
rm $path/outputSylSort/*.txt
rm $path/outputCombo/*.txt
rm $path/outputRandom/*.txt

rm $path/outputFull/*.txt~
rm $path/outputTweet/*.txt~
rm $path/outputSylSort/*.txt~
rm $path/outputCombo/*.txt~
rm $path/outputRandom/*.txt~

rm $path/outputFull/#*.txt#
rm $path/outputTweet/#*.txt#
rm $path/outputSylSort/#*.txt#
rm $path/outputCombo/#*.txt#
rm $path/outputRandom/#*.txt#

rmdir $path/outputFull
rmdir $path/outputTweet
rmdir $path/outputSylSort
rmdir $path/outputCombo
rmdir $path/outputRandom
