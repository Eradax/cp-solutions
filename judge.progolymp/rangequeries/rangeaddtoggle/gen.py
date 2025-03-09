#!/usr/bin/env python3
from random import randint

N = 5
Q = 5

n = randint(1, N)
q = randint(1, Q)

print(n, q)

for _ in range(q):
    t = randint(1, 3)
    l = randint(0, n - 1)
    r = randint(l, n - 1)

    if (t == 1 or t == 3):
        print(t, l, r)
    else:
        v = randint(1, 9)
        print(t, l, r, v)
