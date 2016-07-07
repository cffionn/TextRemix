#!/usr/bin/python

from sklearn import svm
import sys

def testScikitLearn(inFileNameGood, inFileNameBad):
  inFileGood = open(inFileNameGood, "r")

  goodList = inFileGood.readlines()

  inFileBad = open(inFileNameBad, "r")

  badList = inFileBad.readlines()


#  clf = svm.SVC(gamma=0.001, C=100.)

#  clf.fit(xFit, yFit)

#  for i in range(0,len(xPredict)):
#    print(clf.predict(xPredict[i:i+1]))
#    print(yPredict[i]) 


nArg = len(sys.argv)
nArg = nArg

if nArg-1 != 2:
  print("Number of arguments, " + str(nArg-1) + ", not equal to 2. sys.exit()")
  for iter in range(0,nArg-1):
    print("Argument " + str(iter) + "/" + str(nArg-2) + ": " + sys.argv[iter+1])

  sys.exit()

testScikitLearn(sys.argv[1], sys.argv[2])
