#!/usr/bin/env python3
from random import randint

N = 10
M = 10
K = 10

MAX_D = 100
MAX_P = 100

n = randint(1, N)
m = randint(1, M)
k = randint(0, K)

print(n, m, k)

d = [randint(1, MAX_D) for _ in range(n)]
g = [randint(1, MAX_D) for _ in range(m)]
p = [2 * randint(1, MAX_D // 2) for _ in range(m)]
r = [randint(1, MAX_D) for _ in range(k)]

print(*d)
print(*g)
print(*p)
print(*r)
