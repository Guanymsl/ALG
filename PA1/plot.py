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

        input_size = df_sort['File'].str.extract(r'(\d+)').astype(int).squeeze()
        cpu_time = df_sort[metric]

        slope, intercept, r_value, p_value, std_err = linregress(
            np.log(input_size), np.log(cpu_time)
        )

        plt.plot(input_size, cpu_time, marker='o', linestyle='-', label=f'{sort_option} (Slope: {slope:.2f})')

    plt.title(f'CPU Time vs Input Size for {case}')
    plt.xlabel('Input Size')
    plt.ylabel('CPU Time (ms)')

    plt.xscale('log')
    plt.yscale('log')

    plt.grid(which='both', linestyle='--', linewidth=0.5)

    plt.minorticks_on()
    plt.grid(which='minor', linestyle=':', linewidth='0.5', alpha=0.7)

    plt.legend()
    plt.tight_layout()

for case in df['Case'].unique():
    df_case = df[df['Case'] == case]
    plot_time(case, df_case, 'CPU Time (ms)')

plt.show()
