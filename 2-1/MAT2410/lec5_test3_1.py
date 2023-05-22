import scipy.stats as stats

# 1-1 물속 구조 전문가 팀의 평균 탐색 시간
mean = 20
lambda_param = 1 / mean
print("\n", lambda_param)

# 1-2
Q2 = stats.expon.cdf(7, scale = 1 / lambda_param)
print(f"처음 일주일 내에 선박을 찾을 확률: {Q2:.3f}")

# 1-3
Q3 = 1 - stats.expon.cdf(28, scale = 1 / lambda_param)
print(f"탐색을 중단할 확률: {Q3:.3f}")
