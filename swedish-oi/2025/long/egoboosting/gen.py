#!/usr/bin/env python3
from random import randint

N = int(5e5)
E = int(1e9)
max_a = int(1e9)

n = randint(1, N)
e = randint(0, E)

a = [randint(1, max_a) for _ in range(n)]

print(n, e)
print(*a)
