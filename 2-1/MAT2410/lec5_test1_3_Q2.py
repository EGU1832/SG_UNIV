import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

bins_ = [0, 0.35, 0.6, 0.8, 1]

for i in range(4):
    random_num = stats.uniform.rvs(0, 1, 30)
    num_of_random_num = np.histogram(random_num, bins = bins_)[0]
    plt.hist(random_num, bins = bins_, linewidth = 0.25, color = 'gray',edgecolor = 'white')
    plt.xticks(bins_)
    plt.yticks(range(0, max(num_of_random_num)+1))
    plt.title(f'counts: {num_of_random_num}')
    plt.savefig(f"Q2_result_{i}.png")
    plt.clf()
