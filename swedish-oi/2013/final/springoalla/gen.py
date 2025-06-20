#!/usr/bin/env python3
from random import randint

N = 2
T = 100_000
L = 40_000

n = randint(1, N)
t = randint(1, T)

l = [2 * randint(1, L // 2) for _ in range(n)]

print(n, t)
print(*l)
