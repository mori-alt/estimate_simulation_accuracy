import pandas as pd
#import plotly.figure_factory as ff
# from plotly.subplots import make_subplots
# import plotly.graph_objects as go
import matplotlib.pyplot as plt
import streamlit as st
import numpy as np
import math
import glob
import csv

# データの一覧取得
# files = glob.glob('./cmake-build-release/csv/*')
files = glob.glob('../cmake-build-release/output_csv/*')
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
def plot_one_circle():
    fig1 = plt.figure()

    point_thickness = 10  # 線みたいになっちゃう

    plt.subplots_adjust(left=0.05, bottom=0.05, right=0.95, top=0.95, wspace=0.1, hspace=0.6)

    flat_idx = 0  # 表示領域の番号指定 0 - 74
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
    plt.savefig('./only_1-single_mixed.pdf')


plot_one_circle()
