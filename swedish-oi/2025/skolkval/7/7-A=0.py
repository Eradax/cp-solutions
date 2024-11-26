#!/usr/bin/env python3
MOD = 10**9 + 7


def ncr(n, r):
    num = den = 1
    for i in range(r):
        num = (num * (n - i)) % MOD
        den = (den * (i + 1)) % MOD
    return (num * pow(den, MOD - 2, MOD)) % MOD


n, k, s, a = map(int, input().split())
ans = (ncr(k - 1, n - 1) * pow(s, n, MOD)) % MOD

print(ans)
