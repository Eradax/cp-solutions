MOD = 10**10

v = 0
n = int(input())
for i in range(1, n + 1):
    v = (v + pow(i, i, MOD)) % MOD

print(v)
