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

# for idx, (i, j) in enumerate(zip(fac, invfac)):
#     if (i * j) % MOD != 1:
#         print(f"{idx = }")
#         print(f"{i, j = }")
#         exit()


def ncr(n, k):
    if not (n >= 0 and k >= 0 and n >= k):
        ans = 0
    else:
        ans = (fac[n] * invfac[k] * invfac[n - k]) % MOD

    # if ans != comb(n, k) % MOD:
    #     print(f"{ans = }")
    #     print(f"{comb(n, k) % MOD = }")
    #     print(f"{n, k = }")

    return ans


n, k, s, a = map(int, input().split())


def solve(k):
    ans = 0
    for i in range(n + 1):
        add = 1
        add = (add * pow(a * k, i, MOD)) % MOD
        add = (add * pow(s, n - i, MOD)) % MOD
        add = (add * ncr(n, i)) % MOD
        add = (add * ncr(k, n - i)) % MOD

        ans = (ans + add) % MOD
    return ans


print((solve(k) - solve(k - 1)) % MOD)
