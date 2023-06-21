import pandas as pd
import matplotlib.pyplot as plt
import streamlit as st
import numpy as np
import math
import glob
import csv
import seaborn as sns

# データの一覧取得
files = glob.glob('../cmake-build-release/output_csv/*')
files = [x.replace('\\', '/') for x in files]

print('input these files')
print(files)

# read all csv data
data_list = list()
for file in files:
    data_list.append(pd.read_csv(file, header=7))

# get header
names = data_list[3].columns.values

# set page config
st.set_page_config(layout="wide")

def genRGBHist(surface_index):
    print('write ' + str(surface_index) + ' surface index')
    r = []
    g = []
    b = []

    fig1 = plt.figure()

    plt.subplots_adjust(left=0.05, bottom=0.05, right=0.95, top=0.95, wspace=0.1, hspace=0.6)

    # set plot area
    ax = fig1.add_subplot(1, 1, 1)
    ax.set_aspect('equal')
    n = 2 + 5 * surface_index

    for movie_num in range(len(files)):
        d = pd.read_csv(files[movie_num], header=7)

        with open(files[movie_num], 'r') as file:
            reader = csv.reader(file)
            data = [row[1] for idx, row in enumerate(reader) if idx == 3]

        # get RGB
        C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values]) / 255.0
        C = C.transpose()

        for rgb in C:
            r.append(rgb[0])
            g.append(rgb[1])
            b.append(rgb[2])

    # set title
    _title = str(int(names[n][3:7])) + 'nm/' + str(int(names[n][10:12])) + '/' + str(int(names[n][17:20])) + 'nm'
    file = str(int(names[n][3:7])) + 'nm_' + str(int(names[n][10:12])) + '_' + str(int(names[n][17:20])) + 'nm'
    print(_title)

    R = np.array(r)
    G = np.array(g)
    B = np.array(b)

    print('for R')
    show_param(R)
    print('for G')
    show_param(G)
    print('for B')
    show_param(B)

    visualize_data(R, file)


def show_param(x):
    print('size')
    print(x.size)

    print('min')
    print(x.min())

    print('max')
    print(x.max())

    print('scale')
    print(x.max() - x.min())

def visualize_data(data, title):
    # ヒストグラム
    plt.figure(figsize=(10, 6))
    plt.hist(data, bins=100, edgecolor='k')
    plt.title('Histogram ' + title)
    plt.savefig('./visualize/hist/' + title + '.png')

    # KDE
    plt.figure(figsize=(10, 6))
    sns.kdeplot(data)
    plt.title('Kernel Density Estimate ' + title)
    plt.savefig('./visualize/kde/' + title + '.png')

    # ボックスプロット
    plt.figure(figsize=(10, 6))
    sns.boxplot(data)
    plt.title('Box Plot ' + title)
    plt.savefig('./visualize/box/' + title + '.png')


genRGBHist(0)



