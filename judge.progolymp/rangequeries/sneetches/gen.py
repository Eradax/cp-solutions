#!/usr/bin/env python3
from random import randint

N = 100
Q = 100

n = randint(N, N)
q = randint(Q, Q)

v = [randint(0, 1) for _ in range(n)]
# v = [randint(1, 1) for _ in range(n)]

print(n, q)
print("".join(map(str, v)))

for _ in range(q):
    t = randint(1, 2)
    l = randint(0, n - 1)
    r = randint(l, n - 1)
    print(t, l, r)
