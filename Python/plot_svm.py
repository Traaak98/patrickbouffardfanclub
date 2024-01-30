import numpy as np
from sklearn.metrics import confusion_matrix, ConfusionMatrixDisplay
import matplotlib.pyplot as plt

file = np.loadtxt("output")
y_true = file[:, 1]
y_pred = file[:, 0]
mtx = confusion_matrix(y_true, y_pred)
disp = ConfusionMatrixDisplay(mtx)
disp.plot()
plt.show()

