import math
import scipy.stats as stats

# 2-1
expected_distance = "n/4.3"
print("\nE(X)의 값:", expected_distance)

# 2-2
n = 5
lambda_param = 4.3
d = stats.gamma.ppf(0.95, n, scale = 1 / lambda_param)
Q2 = d * 100
print(f"d의 값: {Q2:.3f}")

# 2-3
Q3 = stats.gamma.cdf(1, n, scale = 1 / lambda_param)
print(f"끝에서 1m 이내에 5번째 균열이 있을 확률: {Q3:.3f}")

