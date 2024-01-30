# -*- coding: utf-8 -*-
"""
Created on Mon Nov 29 22:26:59 2021

@author: Louis
"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

dataset = '../SVM/data/dataset_test.csv'
Fe = 22050

file = pd.read_csv(dataset, header=None).to_numpy()
print(file.shape)
test_line = np.arange(0, 10, 1)
print(test_line)

test_lines = file[test_line]
print(test_lines.shape)

fig = plt.figure("features")
axes = fig.subplots(1, 2)

for line in range(test_lines.shape[0]):
    data = test_lines[line].flatten()
    d_m = data[:512]
    d_sig = data[512:-1]
    label = float(data[-1])

    # d_m = np.fft.fftshift(d_m)
    # d_sig = np.fft.fftshift(d_sig)

    axes[0].plot(d_m)
    axes[0].set_title('Moyenne')
    axes[1].plot(d_sig)
    axes[1].set_title('Ecart-type')

plt.show()


# print(abs(d_m0 - d_m))
# print(abs(d_m0 - d_m) < 0.01)

