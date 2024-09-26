import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import linregress

df = pd.read_csv('./sort_results.csv')
df['Case'] = df['File'].apply(lambda x: x.split('.')[1])

def plot_time(case, df_case, metric):
    plt.figure(figsize=(8, 6))
    unique_sorts = df_case['Sort Option'].unique()

    for sort_option in unique_sorts:
        df_sort = df_case[df_case['Sort Option'] == sort_option]
        x = np.log(df_sort['File'].str.extract(r'(\d+)').astype(int).values.flatten())
        y = np.log(df_sort[metric])

        plt.plot(x, y, marker='o', label=f'{sort_option} (Slope: {linregress(x, y).slope:.2f})')

    plt.title(f'CPU Time vs Input Size for {case}')
    plt.xlabel('Log of Input Size')
    plt.ylabel('Log of CPU Time (ms)')
    plt.legend()
    plt.grid(True)

for case in df['Case'].unique():
    df_case = df[df['Case'] == case]

    plot_time(case, df_case, 'CPU Time (ms)')

plt.show()
