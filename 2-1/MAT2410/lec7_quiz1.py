import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

Q1 = stats.norm.ppf(1 - 0.025)
print(f"{Q1:.3f}")

Q2 = stats.norm.ppf(1 - 0.005)
print(f"{Q2:.3f}")

Q3 = stats.norm.ppf(1 - 0.15)
print(f"{Q3:.3f}")

Q4 = stats.t.ppf(1 - 0.05, df = 19)
print(f"{Q4:.3f}")

Q5 = stats.t.ppf(1 - 0.025, df = 19)
print(f"{Q5:.3f}")

Q6 = stats.t.ppf(1 - 0.005, df = 19)
print(f"{Q6:.3f}")

Q7 = stats.t.ppf(1 - 0.01, df = 19)
print(f"{Q7:.3f}")

Q8 = stats.chi2.ppf(1 - 0.05, df = 19)
print(f"{Q8:.3f}")

Q9 = stats.chi2.ppf(1 - 0.95, df = 19)
print(f"{Q9:.3f}")

Q11 = 2 * (1 - stats.norm.cdf(1.581))
print(f"{Q11:.3f}")

Q12 = (stats.norm.cdf(-2.316))
print(f"{Q12:.3f}")

Q13 = 2 * (stats.t.cdf(x = 1.7545, df = 15) - 0.5)
print(f"{Q13:.3f}")

Q14 = 2 * (1 - stats.t.cdf(x = 3.61, df = 23))
print(f"{Q14:.3f}")

Q15 = (1 - stats.t.cdf(x = 1.12, df = 35))
print(f"{Q15:.3f}")

Q16 = 2 * (1 - stats.t.cdf(x = 6.201, df = 28))
print(f"{Q16:.3f}")

Q17 = stats.t.cdf(x = -4.5, df = 39)
print(f"{Q17:.3f}")






