import pandas as pd
import matplotlib.pyplot as plt
import streamlit as st
import numpy as np
import math
import glob
import csv
import pathlib

# データの一覧取得
read_dir_name = '20'
files = glob.glob('../cmake-build-release/csv_' + read_dir_name + '/*')
files = [x.replace('\\', '/') for x in files]
print(files)

# 一覧のデータからcsvの読み込み
data_list = list()
for file in files:
    data_list.append(pd.read_csv(file, header=7))

data = pd.read_csv(files[3], header=7)

st.set_page_config(layout="wide")

# ヘッダの抽出
names = data.columns.values


# 読み込んだcsvをpdfにして出力
# １つの構造について，円を１種類だけ出力する
def plot_one_circle(flat_idx):
    print('plot ' + str(flat_idx) + ' circle')
    fig1 = plt.figure()

    point_thickness = 10

    plt.subplots_adjust(left=0.05, bottom=0.05, right=0.95, top=0.95, wspace=0.1, hspace=0.6)

    # ax = fig1.add_subplot(ny1, nx1, flat_idx+1)  # 表示領域の指定
    ax = fig1.add_subplot(1, 1, 1)
    ax.set_aspect('equal')
    n = 2 + 5 * flat_idx  # 最初の時間と角度を抜いて列番号をとる

    for movie_num in range(len(files)):
        d = pd.read_csv(files[movie_num], header=7)
        # 適切なスケーリングの計算
        # CSVファイルを開く
        with open(files[movie_num], 'r') as file:
            # CSVファイルを読み込む
            reader = csv.reader(file)
            # 指定された行と列のデータを取得する
            data = [row[1] for idx, row in enumerate(reader) if idx == 3]

        camera_theta = float(data[0])
        range_scale = camera_theta / 90
        # RGBデータの取得
        C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values]) / 255.0
        C = C.transpose()

        # 角度を計算する
        theta = np.radians(d.iloc[:, n].values)
        phi = np.radians(d.iloc[:, n + 1].values)
        x = theta / (math.pi * 0.5) * np.cos(phi)
        y = theta / (math.pi * 0.5) * np.sin(phi)
        ax.scatter(x * range_scale, y * range_scale, c=C, s=point_thickness)

    ax.axes.xaxis.set_visible(False)
    ax.axes.yaxis.set_visible(False)

    # タイトルの作成
    _name = str(int(names[n][3:7])) + 'nm/' + str(int(names[n][10:12])) + '/' + str(int(names[n][17:20])) + 'nm'
    ax.set_title(_name, fontsize=4)

    st.write(fig1)
    _output_file_name = str(int(names[n][3:7])) + 'nm_' + str(int(names[n][10:12])) + '_' + str(int(names[n][17:20])) + 'nm'
    print('output ' + _output_file_name)
    pathlib.Path('./single/' + read_dir_name + '_png').mkdir(exist_ok=True)
    plt.savefig('./single/' + read_dir_name + '_png/' + _output_file_name + '.png')


# ringをマスク処理を掛けながら表示すること
def masked_plot_one_circle(flat_idx, max_point):
    print('plot ' + str(flat_idx) + ' circle')
    fig1 = plt.figure()

    point_thickness = 10

    plt.subplots_adjust(left=0.05, bottom=0.05, right=0.95, top=0.95, wspace=0.1, hspace=0.6)

    # ax = fig1.add_subplot(ny1, nx1, flat_idx+1)  # 表示領域の指定
    ax = fig1.add_subplot(1, 1, 1)
    ax.set_aspect('equal')
    n = 2 + 5 * flat_idx  # 最初の時間と角度を抜いて列番号をとる

    for movie_num in range(len(files)):
        d = pd.read_csv(files[movie_num], header=7)
        # 適切なスケーリングの計算
        # CSVファイルを開く
        with open(files[movie_num], 'r') as file:
            # CSVファイルを読み込む
            reader = csv.reader(file)
            # 指定された行と列のデータを取得する
            data = [row[1] for idx, row in enumerate(reader) if idx == 3]

        camera_theta = float(data[0])
        range_scale = camera_theta / 90
        # RGBデータの取得
        C = np.array([d.iloc[:, n + 2].values, d.iloc[:, n + 3].values, d.iloc[:, n + 4].values]) / max_point
        C = C.transpose()

        # update rgb over 1.0 to 0.0
        for c in C:
            if c[0] > 1.:
                c[0] = 0
                print('c[0] is over 1.0')

            if c[1] > 1.:
                c[1] = 0.
                print('c[1] is over 1.0')

            if c[2] > 1.:
                c[2] = 0.
                print('c[2] is over 1.0')

        # 角度を計算する
        theta = np.radians(d.iloc[:, n].values)
        phi = np.radians(d.iloc[:, n + 1].values)
        x = theta / (math.pi * 0.5) * np.cos(phi)
        y = theta / (math.pi * 0.5) * np.sin(phi)
        ax.scatter(x * range_scale, y * range_scale, c=C, s=point_thickness)

    ax.axes.xaxis.set_visible(False)
    ax.axes.yaxis.set_visible(False)

    # タイトルの作成
    _name = str(int(names[n][3:7])) + 'nm/' + str(int(names[n][10:12])) + '/' + str(int(names[n][17:20])) + 'nm / max index: ' + str(max_point)
    ax.set_title(_name, fontsize=4)


    st.write(fig1)
    _output_file_name = str(int(names[n][3:7])) + 'nm_' + str(int(names[n][10:12])) + '_' + str(int(names[n][17:20])) + 'nm'
    print('output ' + _output_file_name)
    pathlib.Path('./single/max_index_' + str(max_point) + '_' + read_dir_name + '_png').mkdir(exist_ok=True)
    plt.savefig('./single/max_index_' + str(max_point) + '_' + read_dir_name + '_png/' + _output_file_name + '.png')


for i in range(48):
    masked_plot_one_circle(i, 10)
