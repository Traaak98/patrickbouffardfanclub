import emlearn
import numpy as np
from sklearn.ensemble import RandomForestClassifier
from sklearn import preprocessing
import pandas as pd
import sklearn.model_selection
import sklearn.metrics

data=pd.read_csv('Audio/dataset.csv', header=None)


X=data.iloc[:,:-1]
X=np.asarray(X)
y=data.iloc[:, -1]
y2=[]
for i in range(len(y)):
    y2.append(y[i].split('.')[0])
y = np.asarray(y2)

# Load data


le = preprocessing.LabelEncoder()
# le.fit(data[])
labels = le.fit(['blues', 'classical', 'country', 'disco', 'hiphop', 'jazz', 'metal', 'pop', 'reggae', 'rock'])
print(list(le.classes_))
le.transform(['blues', 'classical', 'country', 'disco', 'hiphop', 'jazz', 'metal', 'pop', 'reggae', 'rock'])
for label in y:
    label = le.transform([label])

    # print(line[-1])

# Train model
X_train, X_test, y_train, y_test = sklearn.model_selection.train_test_split(X, y, test_size=0.25, random_state=1)

estimator = RandomForestClassifier(n_estimators=100, max_depth=20)
estimator.fit(X_train, y_train)
score = estimator.score(X_test, y_test)

print('sklearn score: ', score)

path = 'random_forest.h'
c_code = emlearn.convert(estimator, method='inline',dtype='float')
c_code.save(file=path, name='random_forest')