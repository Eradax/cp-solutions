#!/usr/bin/env python3
from random import randint

N = int(2e5)
Q = int(2e5)
MAXA = int(1e12)

# n = randint(1, N)
# q = randint(1, Q)
n = N
q = Q

a = [randint(0, MAXA) for _ in range(n)]

queries = []
for _ in range(q):
    op = randint(0, 3)
    v = []
    if op == 0:
        l = randint(0, n - 1)
        r = randint(l + 1, n)
        b = randint(-MAXA, MAXA)
        v = [op, l, r, b]
    elif op == 1:
        l = randint(0, n - 1)
        r = randint(l + 1, n)
        b = randint(-MAXA, MAXA)
        v = [op, l, r, b]
    elif op == 2:
        l = randint(0, n - 1)
        r = randint(l + 1, n)
        b = randint(-MAXA, MAXA)
        v = [op, l, r, b]
    elif op == 3:
        l = randint(0, n - 1)
        r = randint(l + 1, n)
        v = [op, l, r]

    queries.append(v)

print(n, q)
print(*a)
for i in queries:
    print(*i)
