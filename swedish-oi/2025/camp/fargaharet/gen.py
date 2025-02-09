#!/usr/bin/env python3
from random import randint

N = int(1e5)
Q = int(1e5)

V = 9

arr = [randint(0, V) for _ in range(N)]

print(N, Q)
print(*arr)

for _ in range(Q):
    print(randint(1, N), randint(0, V))

