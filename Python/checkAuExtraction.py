# -*- coding: utf-8 -*-
"""
Created on Mon Nov 29 22:26:59 2021

@author: Louis
"""
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

file_au = 'blues.00000.au'
file_m = 'fft_mean.csv'
file_sig = 'fft_sigma.csv'
Fe = 22050


def readAuFile(file):
    with open(file, 'rb') as au:
        magic_number = au.read(4)
        print("Magical number: Ox%x" % int.from_bytes(magic_number, byteorder='big'))
        dataoffset = int.from_bytes(au.read(4), byteorder='big', signed=True)
        print("Data offset: %d" % dataoffset)
        datasize = int.from_bytes(au.read(4), byteorder='big', signed=True)
        print("Data size: %d" % datasize)
        au.seek(0)
        au.read(dataoffset)
        data = au.read(datasize)

    d = []
    for i in range(0, datasize, 2):
        d.append(int.from_bytes(data[i:i + 2], byteorder='big', signed=True))
    d = np.asarray(d, dtype=np.int16)
    return d


d_m = pd.read_csv(file_m, header=None)
d_m = d_m.to_numpy()
d_m = d_m.reshape((d_m.shape[1],))
data = d_m[0]
data = data.split()
data = data[1:]

d_m = np.zeros((512,))
i = 0
for e in data[:512]:
    e = e.split(':')
    d_m[i] += float(e[1])
    i += 1

d_sig = np.zeros((512,))
i = 0
for e in data[512:]:
    e = e.split(':')
    d_sig[i] += float(e[1])
    i += 1

# d_sig = pd.read_csv(file_sig, header=None)
# d_sig = d_sig.to_numpy()
# d_sig = d_sig.reshape((d_sig.shape[1],))

d_m = np.fft.fftshift(d_m)
d_sig = np.fft.fftshift(d_sig)

fig = plt.figure("nous")
axes = fig.subplots(1, 2)
axes[0].plot(d_m)
axes[0].set_title('Moyenne')
axes[1].plot(d_sig)
axes[1].set_title('Ecart-type')

dataset = pd.read_csv('../Audio/dataset.csv', header=None).to_numpy()
print(dataset.shape)
dataset = dataset[0]
print(dataset)
print(dataset.shape)
d_m0 = dataset[:512]
d_sig0 = dataset[512:-1]
print(dataset[-1])
d_m0 = np.fft.fftshift(d_m0)
d_sig0 = np.fft.fftshift(d_sig0)

fig0 = plt.figure("levrai")
axes = fig0.subplots(1, 2)
axes[0].plot(d_m0)
axes[0].set_title('Moyenne')
axes[1].plot(d_sig0)
axes[1].set_title('Ecart-type')


# print(abs(d_m0 - d_m))
# print(abs(d_m0 - d_m) < 0.01)
plt.show()
