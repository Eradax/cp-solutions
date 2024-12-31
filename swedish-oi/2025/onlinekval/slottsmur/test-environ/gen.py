#!/usr/bin/env python3
import random
import sys


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default


N = int(cmdlinearg('n', 2e5))
Q = int(cmdlinearg('q', 2e5))
H_MAX = int(cmdlinearg('h', 1e9))

per = int(cmdlinearg('per', 50))

Q1 = Q * per // 100
Q2 = Q - Q1

T = [1] * Q1 + [2] * Q2
random.shuffle(T)

n, q = N, Q
h = [random.randint(1, H_MAX) for _ in range(n)]

print(n, q)
print(*h)

for i in range(q):
    if T[i] == 1:
        l = random.randint(1, n - 1)
        r = random.randint(l + 1, n)

        print(T[i], l, r)
    else:
        ind = random.randint(1, n)

        while h[ind - 1] >= H_MAX:
            ind = random.randint(1, n)

        w = random.randint(1, H_MAX - h[ind - 1])

        h[ind - 1] += w

        print(T[i], ind, w)
