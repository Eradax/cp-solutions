
import numpy as np

def sum_topK(n: int, m: int, K: int) -> float:
    # Base polynomial P(x) = (1 + x + ... + x^{n-1})/n
    base = np.ones(n, dtype=np.float64) / n

    # Compute P(x)^m by repeated convolution
    res = base.copy()
    for _ in range(m - 1):
        res = np.convolve(res, base)

    # Pick off the K largest coefficients and sum them
    topK = np.sort(res)[-K:]
    return topK.sum()

if __name__ == '__main__':
    m, n, K = map(int, input().split())
    ans = sum_topK(n, m, K)
    # Print with plenty of precision
    print(f"{ans:.15f}")
