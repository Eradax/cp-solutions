#!/usr/bin/env python3

n = int(input())

line = [int(i) for i in input().split()]

dp0 = [0] * n
dp1 = [0] * n

dp1[0] = line[0]

for i in range(n - 1):
    dp0[i + 1] = dp1[i]
    dp1[i + 1] = line[i + 1] + min(dp0[i], dp1[i])

print(min(dp0[n - 1], dp1[n - 1]))
