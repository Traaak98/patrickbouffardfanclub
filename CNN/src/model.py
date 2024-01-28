import tensorflow as tf
from tensorflow.keras import layers, models
import sklearn.model_selection
import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt

# Mise en place des datas :
data=pd.read_csv('dataset.csv', header=None)
X=data.iloc[:,:-1]
X=np.asarray(X)
y=data.iloc[:, -1]
y2=[]
for i in range(len(y)):
    y2.append(y[i].split('.')[0])
y = np.asarray(y2)
scaler_X = StandardScaler()
X_scaled = scaler_X.fit_transform(X)

# Encoder les labels
le = LabelEncoder()
y_val = le.fit_transform(y)

X_train, X_test, y_train, y_test = sklearn.model_selection.train_test_split(X_scaled, y_val, test_size=0.25, random_state=1)
print(X_train.shape) # (750, 1024)
print(X_test.shape) # (250, 1024)
print(y_train.shape) # (750,)
print(y_test.shape) # (250,)

def create_model(filters=64, kernel_size=3, pool_size=2, dense_units=128, dropout_rate=0.5):
    model = models.Sequential([
        layers.Input(shape=(1024,1)),
        layers.Conv1D(filters, kernel_size, activation='relu'),
        layers.MaxPooling1D(pool_size),
        layers.Flatten(),
        layers.Dense(dense_units, activation='relu'),
        layers.Dropout(dropout_rate),
        layers.Dense(10, activation='softmax'),
    ])
    return model

param_grid = {
    'filters': [32, 64, 128],
    'kernel_size': [3, 5],
    'pool_size': [2, 3],
    'dense_units': [64, 128, 256],
    'dropout_rate': [0.3, 0.5, 0.7]
}

model = create_model(filters=32, kernel_size=5, pool_size=2, dense_units=128, dropout_rate=0.7)

model.summary()

model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])


result = model.fit(X_train, y_train, epochs=50, validation_data=(X_test, y_test))

metrics = result.history
plt.figure(figsize=(16,6))
plt.subplot(1,2,1)
plt.plot(result.epoch, metrics['loss'], metrics['val_loss'])
plt.legend(['loss', 'val_loss'])
plt.ylim([0, max(plt.ylim())])
plt.xlabel('Epoch')
plt.ylabel('Loss [CrossEntropy]')

plt.subplot(1,2,2)
plt.plot(result.epoch, 100*np.array(metrics['accuracy']), 100*np.array(metrics['val_accuracy']))
plt.legend(['accuracy', 'val_accuracy'])
plt.ylim([0, 100])
plt.xlabel('Epoch')
plt.ylabel('Accuracy [%]')



# confusion matrix
from sklearn.metrics import confusion_matrix
import seaborn as sns
y_pred = model.predict(X_test)
y_pred_classes = np.argmax(y_pred, axis=1)
y_true = y_test
cm = confusion_matrix(y_true, y_pred_classes)
plt.figure(figsize=(10,10))
sns.heatmap(cm, annot=True, fmt="d")
plt.xlabel('Predicted')
plt.ylabel('Truth')

plt.show()


# Convertir le modèle en format TensorFlow Lite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()

# Sauvegarder le modèle TensorFlow Lite en tant que fichier .tflite
with open('model.tflite', 'wb') as f:
    f.write(tflite_model)