#!/usr/bin/env python3
from random import randint

N = 1000
Q = 1000
A = int(1e6)

n = randint(1, N)
q = randint(1, Q)

a = [randint(0, A) for _ in range(n)]

queries = []
for _ in range(q):
    l = randint(1, n)
    r = randint(l, n)
    queries.append((l, r))

print(n, q)
print(*a)
for i in queries:
    print(*i)
