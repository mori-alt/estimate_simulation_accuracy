import pandas as pd
import matplotlib.pyplot as plt
import streamlit as st
import numpy as np
import glob
import seaborn as sns

# get data
files = glob.glob('../cmake-build-release/output_csv_20/*')
files = [x.replace('\\', '/') for x in files]

print('input these files')
print(files)

# read all csv data
data_list = list()
for file in files:
    data_list.append(pd.read_csv(file, header=7))

# get header
names = data_list[3].columns.values


def genRGBHist(surface_index):
    # set page config
    st.set_page_config(layout="wide")
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

        # get RGB
        C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values])
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

    visualize_data(R, G, B, file)


# 構造毎のRGBの最大値と最小値を求める
def getRGBMax():
    max_values = np.zeros(48)
    for i in range(48):
        surface_index = i
        print('get max RGB in ' + str(surface_index))
        n = 2 + 5 * surface_index
        max_value = 0

        # 全てのファイルを読み込む (表面構造毎に処理を行う)
        for movie_num in range(len(files)):
            d = pd.read_csv(files[movie_num], header=7)

            # get RGB
            C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values])
            C = C.transpose()

            max_value = max(max_value, np.max(C))

        max_values[i] = max_value

    print('all max values')
    print(max_values)

    print('max RGB')
    print(np.max(max_values))
    sns.lineplot(data=max_values)
    plt.title('MAX_RGB : ' + str(np.max(max_values)))
    # plt.show()
    plt.savefig('./visualize/distribution/max_lineplot.png')

    return max_values

def plotRGBDistributionHeatmap():
    print('plot heatmap')
    divide_num = 255
    distribution = np.zeros((48, divide_num))
    mask_index = 5

    # each surface
    for i in range(48):
        surface_index = i
        n = 2 + 5 * surface_index
        print(i)

        # each file
        for movie_num in range(len(files)):
            d = pd.read_csv(files[movie_num], header=7)

            # get RGB
            C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values])
            C = C.transpose()

            for c in C:
                # round to int
                r = int(c[0])
                g = int(c[1])
                b = int(c[2])

                distribution[i][r] = 1 + distribution[i][r]
                distribution[i][b] = 1 + distribution[i][b]
                distribution[i][g] = 1 + distribution[i][g]

                distribution[i][:mask_index] = 0
                distribution[i][:mask_index] = 0
                distribution[i][:mask_index] = 0

    sns.heatmap(distribution)
    plt.savefig('./visualize/distribution/' + str(mask_index) + '_masked_RGB_distribution.png')

def plot01RGBDistributionHeatmap():
    print('plot heatmap')
    distribution_max = 25
    divide_num = 255
    distribution = np.zeros((48, divide_num))

    # each surface
    for i in range(48):
        surface_index = i
        n = 2 + 5 * surface_index
        print(i)

        # each file
        for movie_num in range(len(files)):
            d = pd.read_csv(files[movie_num], header=7)

            # get RGB
            C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values])
            C = C.transpose()

            for c in C:
                # round to int
                r = int(c[0])
                g = int(c[1])
                b = int(c[2])

                distribution[i][r] = 1
                distribution[i][b] = 1
                distribution[i][g] = 1


    sns.heatmap(distribution)
    plt.savefig('./visualize/distribution/01RGB_distribution.png')


def show_param(x):
    print('size')
    print(x.size)

    print('min')
    print(x.min())

    print('max')
    print(x.max())

    print('scale')
    print(x.max() - x.min())


def visualize_data(R_data, G_data, B_data, title):
    # ヒストグラム
    plt.figure(figsize=(10, 6))
    sns.histplot(R_data, color='red', bins=100)
    sns.histplot(G_data, color='green', bins=100)
    sns.histplot(B_data, color='blue', bins=100)

    plt.title('Histogram ' + title)
    plt.savefig('./visualize/hist/' + title + '.png')

    # KDE
    plt.figure(figsize=(10, 6))
    sns.kdeplot(R_data)
    plt.title('Kernel Density Estimate ' + title)
    plt.savefig('./visualize/kde/' + title + '.png')

    # ボックスプロット
    plt.figure(figsize=(10, 6))
    sns.boxplot(R_data)
    plt.title('Box Plot ' + title)
    plt.savefig('./visualize/box/' + title + '.png')


# make hist kde box
# for i in range(48):
#     genRGBHist(i)


getRGBMax()
# plotRGBDistributionHeatmap()
# plot01RGBDistributionHeatmap()

