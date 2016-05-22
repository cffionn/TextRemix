from sklearn import svm

'''
FIT
of the sea written in the state of film and Advil,11,13,0
of the plastic anthem,4,6,0
you even lift that cannon?,5,7,0
At least what's never had can't be lost, the state of film and Advil,14,16,0
you but some alarmed pretender, I was),7,10,0
that cannon?,2,3,0
even as you savage?,4,6,0
even lift that cannon?,4,6,0
At least what's never had can't be lost, the very fabric,11,14,0
you savage?,2,3,0
a savage savage,3,5,0
running, shouting now into the state of film and Advil,10,14,0
of the parish,3,4,0
At least what's never had can't be lost, the masses,10,12,1
running, shouting now into the water wash over my sins?,10,15,1
of self stuck with innocent passage,6,9,1
a lullaby in the state of film and Advil,9,12,1
you but some alarmed pretender, I went on boulevard Madville,10,16,1
been incinerated, I've oft returned to mass attacking,8,15,1
of the wind be beneath my wings?,7,8,1
At least what's never had can't be lost, the rhythm of the plastic anthem,14,18,1
a lullaby in the very fabric,6,10,1
running, shouting now into the wind be beneath my wings?,10,14,1
At least what's never had can't be lost, the parish,10,12,1
'''

xFit = [
  [11,13]
  [4,6]
  [5,7]
  [14,16]
  [7,10]
  [2,3]
  [4,6]
  [4,6]
  [11,14]
  [2,3]
  [3,5]
  [10,14]
  [3,4]
  [10,12]
  [10,15]
  [6,9]
  [9,12]
  [10,16]
  [8,15]
  [7,8]
  [14,18]
  [6,10]
  [10,14]
  [10,12]
]

yFit = [
  0
  0
  0
  0
  0
  0
  0
  0
  0
  0
  0
  0
  0
  1
  1
  1
  1
  1
  1
  1
  1
  1
  1
  1
  ]

xPredict = [

  ]

yPredict = [
  
  ]

def main:
  clf = svm.SVC(gamma=0.001, C=100.)

  clf.fit(xFit, yPredict)
  
