#!/usr/bin/env python3
from random import randint

T = 2
N = 10
M = 10

for _ in range(T):
    n = randint(1, N)
    m = randint(1, M)

    print(n, m)

    for _ in range(m):
        t = randint(1, 3)
        if t == 3:
            p = randint(1, n)
            print(t, p)
        else:
            p, q = [randint(1, n) for _ in range(2)]
            print(t, p, q) 
