#!/usr/bin/env python3
from random import randint

MAXN = 1000

n = randint(1, MAXN)
k = randint(1, n)

vals = [-1] * n

for i in range(1, k + 1):
    a = randint(0, n - 1)
    while vals[a] != -1:
        a = randint(0, n - 1)

    vals[a] = i

for i in range(n):
    if vals[i] == -1:
        vals[i] = randint(1, k)

print(n, k)
print(*vals)
