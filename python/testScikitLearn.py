from sklearn import svm

xFit = [

  ]

yFit = [
  
  ]

xPredict = [

  ]

yPredict = [
  
  ]

def main:
  clf = svm.SVC(gamma=0.001, C=100.)

  clf.fit(x, y)
  
