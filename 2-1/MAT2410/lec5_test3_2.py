import math
import scipy.stats as stats

# 2-1
lambda_param = 4.3
print("\nλ의 값:", lambda_param)

# 2-2
gap_length = 0.1
Q2 = stats.expon.cdf(gap_length, scale = 1 / lambda_param)
print(f"간격이 10cm보다 짧을 확률: {Q2:.3f}")

# 2-3
gap_length = 0.3
Q3 = 1 - stats.expon.cdf(gap_length, scale = 1 / lambda_param)
print(f"간격이 30cm보다 긴 확률: {Q3:.3f}")

# 2-4
segment_length = 0.25 
poisson_mean = 42 * segment_length
Q4 = 1 - stats.poisson.pmf(0, poisson_mean) - stats.poisson.pmf(1, poisson_mean)
print(f"적어도 2개의 균열이 있는 확률: {Q4:.3f}")
