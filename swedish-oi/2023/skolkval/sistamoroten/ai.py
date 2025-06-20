import sys
import math
from functools import lru_cache

# Standard normal PDF & CDF
def phi(x): return math.exp(-0.5*x*x)/math.sqrt(2*math.pi)
def Phi(x): return 0.5 * math.erfc(-x / math.sqrt(2))

# Cumulant-generating function and derivatives for sum of m Uniform{0,...,n-1}
def K_fn(t, n, m):
    et, ent = math.exp(t), math.exp(n*t)
    return m * (math.log((ent - 1)/(et - 1)) - math.log(n))

def K1_fn(t, n, m):
    et, ent = math.exp(t), math.exp(n*t)
    denom1 = ent - 1
    denom2 = et - 1
    if abs(denom1) < 1e-12 or abs(denom2) < 1e-12:
        raise ValueError("Numerical instability in K1")
    return m * (n * ent / denom1 - et / denom2)

def K2_fn(t, n, m):
    et, ent = math.exp(t), math.exp(n*t)
    denom1 = (ent - 1)**2
    denom2 = (et - 1)**2
    if abs(denom1) < 1e-12 or abs(denom2) < 1e-12:
        raise ValueError("Numerical instability in K2")
    return m * (n*n * ent * (ent + 1) / denom1 - et * (et + 1) / denom2)

# Saddlepoint CDF approximation for discrete S at threshold s
def saddle_cdf(s, n, m):
    x = s + 0.5
    t = 1e-6
    for _ in range(50):
        try:
            f = K1_fn(t, n, m) - x
            fp = K2_fn(t, n, m)
            t_new = t - f/fp
            if abs(t - t_new) < 1e-12:
                break
            t = t_new
        except ValueError:
            t *= 0.5
    k = K_fn(t, n, m)
    k2 = K2_fn(t, n, m)
    delta = 2*(t*x - k)
    if delta < 0:
        return 0.0
    r = math.copysign(math.sqrt(delta), t)
    q = t * math.sqrt(k2)
    return Phi(r) + phi(r)*(1/r - 1/q)

@lru_cache(maxsize=None)
def exact_cdf(s, n, m):
    # Compute probability mass via DP convolution
    max_val = m * (n - 1)
    dp = [0.0] * (max_val + 1)
    dp[0] = 1.0
    for _ in range(m):
        ndp = [0.0] * (max_val + 1)
        for i in range(len(dp)):
            if dp[i] > 0:
                for v in range(n):
                    if i + v < len(ndp):
                        ndp[i + v] += dp[i] / n
        dp = ndp
    return sum(dp[:s+1])

# Sum of top-K probabilities
def sum_topK(n, m, K):
    if m <= 20:
        mu = m*(n-1)/2.0
        L = math.floor(mu - (K-1)/2.0)
        R = L + K - 1
        return exact_cdf(R, n, m) - exact_cdf(L - 1, n, m)
    mu = m*(n-1)/2.0
    L = math.floor(mu - (K-1)/2.0)
    R = L + K - 1
    cdf_R = saddle_cdf(R, n, m)
    cdf_Lm1 = saddle_cdf(L-1, n, m)
    return max(0.0, min(1.0, cdf_R - cdf_Lm1))

if __name__ == '__main__':
    n, m, K = map(int, sys.stdin.read().split())
    ans = sum_topK(n, m, K)
    print(f"{ans:.15f}")
