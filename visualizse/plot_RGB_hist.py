import pandas as pd
import matplotlib.pyplot as plt
import streamlit as st
import numpy as np
import math
import glob
import csv

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
# data = pd.read_csv(files[3], header=7)
names = data_list[0].columns.values
print(names)

# set page config
st.set_page_config(layout="wide")

def genRGBHist(surface_index):
    print('write ' + str(surface_index) + ' surface index')
