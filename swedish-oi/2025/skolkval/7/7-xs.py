#!/usr/bin/env python3
MOD = 10**9 + 7

n, k, s, a = map(int, input().split())

dp = [[-1 for _ in range(k + 5)] for _ in range(n + 5)]


def f(x, y):
    if dp[x][y] != -1:
        return dp[x][y]

    if x == 1:
        dp[x][y] = ((a + s) * y) % MOD
        return ((a + s) * y) % MOD

    ans = 0
    for i in range(y + 1)[::-1]:
        tmp = f(x - 1, i) % MOD
        tmp *= x * (s if y != i else a * i)

        ans += tmp
        ans %= MOD

    dp[x][y] = ans
    return ans


f(n, k)
f(n, k - 1)


print(f"{f(n, k) = }")
print(f"{f(n, k - 1) = }")

print(f(n, k) - f(n, k - 1))

for i in dp:
    print(*i)
