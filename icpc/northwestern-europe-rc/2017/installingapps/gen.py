#!/usr/bin/env python3
from random import randint

N = 15
C = 100

MAX_DS = C

n = randint(1, N)
c = randint(1, C)

d = [randint(1, MAX_DS) for _ in range(n)]
s = [randint(1, MAX_DS) for _ in range(n)]

print(n, c)
for v in zip(d, s):
    print(*v)
