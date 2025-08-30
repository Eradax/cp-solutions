#!/usr/bin/env python3
from random import randint
from random import choice

N = 10**5
Q = 10**6

n = randint(2, N)
q = randint(1, Q)

print(n, q)

sz = [0] + [1] * n
tags = []

cnt = 0
while cnt < q:
    cnt += 1

    op = randint(1, 3)

    if op == 1:
        i = randint(1, n)
        while sz[i] == 0:
            i = randint(1, n)
        j = randint(1, sz[i])

        print(op, i, j)
    
    if op == 2:
        i = randint(1, n)
        while sz[i] == 0:
            i = randint(1, n)

        j = randint(1, n)
        while i == j:
            j = randint(1, n)

        tags.append(j)
        sz[i] += sz[j]
        sz[j] = 0

        print(op, i, j)

    if op == 3:
        if len(tags) == 0:
            cnt -= 1
            continue

        i = randint(1, n)
        while sz[i] == 0:
            i = randint(1, n)

        j = randint(0, sz[i])

        sz[tags[-1]] = sz[i] - j
        sz[i] = j

        tags.pop()

        print(op, i, j)
