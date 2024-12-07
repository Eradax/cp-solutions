#!/usr/bin/env python3
MOD = 10**9 + 7
MAXNK = 2 * 10**5 + 1

fac = [1] * MAXNK
for i in range(1, MAXNK):
    fac[i] = (i * fac[i - 1]) % MOD

inv = [1] * MAXNK
for i in range(2, MAXNK):
    inv[i] = (MOD - MOD // i) * inv[MOD % i] % MOD

invfac = [1] * MAXNK
for i in range(2, MAXNK):
    invfac[i] = (invfac[i - 1] * inv[i]) % MOD


def ncr(n, k):
    if not (n >= 0 and k >= 0 and n >= k):
        ans = 0
    else:
        ans = (fac[n] * invfac[k] * invfac[n - k]) % MOD

    return ans


n, k, s, a = map(int, input().split())

spow = [1] * MAXNK
for i in range(1, MAXNK):
    spow[i] = (spow[i - 1] * s) % MOD

akpow = [[1] * MAXNK for _ in range(2)]

p = (a * k) % MOD
for i in range(1, MAXNK):
    akpow[1][i] = (akpow[1][i - 1] * p) % MOD

p = (a * (k - 1)) % MOD
for i in range(1, MAXNK):
    akpow[0][i] = (akpow[0][i - 1] * p) % MOD


def solve(nn, kk, ind):
    ans = 0
    for i in range(nn + 1):
        add = 1
        add = (add * akpow[ind][i]) % MOD
        add = (add * spow[nn - i]) % MOD
        add = (add * ncr(nn, i)) % MOD
        add = (add * ncr(kk, nn - i)) % MOD
    
        ans = (ans + add) % MOD
    return ans


print((solve(n, k, 1) - solve(n, k - 1, 0)) % MOD)

