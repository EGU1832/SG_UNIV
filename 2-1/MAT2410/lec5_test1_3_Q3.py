import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

bins_ = [0, 0.35, 0.6, 0.8, 1]
count = []

for i in range(100):
    random_num = stats.uniform.rvs(0, 1, 30)
    num_of_random_num = np.histogram(random_num, bins = bins_)[0]
    count.append(num_of_random_num)

count_arr = np.array(count)
exp_count = np.mean(count_arr, axis = 0)
var_count = np.var(count_arr, axis = 0)

print(f"Expectaion of random numbers in each interval: {exp_count}")
print(f"Varience of random numbers in each interval: {var_count}")
