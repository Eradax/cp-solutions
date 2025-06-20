#!/usr/bin/env python3
from random import randint

N = randint(1, 25)
K = N

MAXA = 1

a = [randint(0, MAXA) for _ in range(N)]

print(N, randint(1, K))
print(*a)
