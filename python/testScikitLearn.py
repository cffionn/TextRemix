from sklearn import svm

'''
FIT
"running, shouting now into the the pastor's masters",8,13,1
"wedding ring, a savage savage",5,8,1
"that all things loved are you savage?",7,8,1
"continuing your fame and Advil",5,9,1
"At least what's never had can't be lost, the gods",10,11,1
"At least what's never had can't be lost, the masses",10,12,1
"When I saw you even lift that cannon?",8,10,1
"been incinerated, I've oft returned to this is over",9,15,1
"At least what's never had can't be lost, the badges",10,12,1
"of the water wash over my sins?",7,9,1
"you but some alarmed pretender, I went on boulevard Madville",10,16,1
"of the badges",3,4,0
"of the plastic anthem",4,6,0
"a savage savage",3,5,0
"When I was)",3,3,0
"umbrella, me claiming I was)",5,8,0
"of the rhythm of the plastic anthem",7,10,0
"even as you savage?",4,6,0
"that cannon?",2,3,0
"At least what's never had can't be lost, the water wash over my sins?",14,17,0
"even lift that cannon?",4,6,0
"of the wind be beneath my wings?",7,8,0
"of the masses",3,4,0
"of the parish",3,4,0
"of self stuck with innocent passage",6,9,0
"of the state of film and Advil",7,8,0

PREDICT
"At least what's never had can't be lost, the very fabric",11,14,1
"running, shouting now into the very fabric",7,12,1
"running, shouting now into the parish",6,10,1
"running, shouting now into the plastic anthem",7,12,1
"a lullaby in the very fabric",6,10,1
"running, shouting now into the state of film and Advil",10,14,1
"running, shouting now into the rhythm of the plastic anthem",10,16,1
"running, shouting now into the badges",6,10,1
"of the sea written in the the pastor's masters",9,12,0
"of the very fabric",4,6,0
"a lullaby in the the pastor's masters",7,11,0
"of the the pastor's masters",5,7,0
"of the sea written in the state of film and Advil",11,13,0
"At least what's never had can't be lost, the state of film and Advil",14,16,0
'''


xFit = [
  [8,13],                                                        
  [5,8],
  [7,8],
  [5,9],
  [10,11],
  [10,12],
  [8,10],
  [9,15],
  [10,12],
  [7,9], 
  [10,16],
  [3,4],
  [4,6],
  [3,5],
  [3,3],
  [5,8],
  [7,10],
  [4,6],
  [2,3],
  [14,17],
  [4,6],
  [7,8],
  [3,4],
  [3,4],
  [6,9],
  [7,8],   
  ]

yFit = [
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1, 
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,   
  ]

xPredict = [
  [11,14],
  [7,12],
  [6,10],
  [7,12],
  [6,10],
  [10,14],
  [10,16],
  [6,10],
  [9,12],
  [4,6],
  [7,11],
  [5,7],
  [11,13],
  [14,16],
    ]

yPredict = [
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,  
    ]

def testScikitLearn():
  clf = svm.SVC(gamma=0.001, C=100.)

  clf.fit(xFit, yFit)

  for i in range(0,len(xPredict)):
    print(clf.predict(xPredict[i:i+1]))
    print(yPredict[i]) 

testScikitLearn()
