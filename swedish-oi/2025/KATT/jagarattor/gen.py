#!/usr/bin/env python3
from random import randint
import random


class UF:
    def __init__(self, n: int) -> None:
        self.e = [-1] * n

    def size(self, x: int) -> int:
        return -self.e[self.find(x)]

    def sameset(self, a: int, b: int) -> bool:
        return self.find(a) == self.find(b)

    def find(self, x: int) -> int:
        if self.e[x] < 0:
            return x
        else:
            self.e[x] = self.find(self.e[x])
            return self.e[x]

    def join(self, a: int, b: int) -> None:
        a = self.find(a)
        b = self.find(b)

        if self.e[a] > self.e[b]:
            a, b = b, a

        self.e[a] += self.e[b]
        self.e[b] = a


N = int(1e5)
M = int(1e5)
Q = int(1e5)

n = N
m = M
q = Q

# N = 5
# M = 5
# Q = 5
#
# n = randint(3, N)
# m = randint(n - 1, min(M, n * (n - 1) // 2))
# q = randint(1, Q)

uf: UF = UF(n)

adj = [[] for _ in range(n + 1)]

edges: set = set()
while len(edges) < n - 1:
    u: int = randint(0, n - 1)
    v: int = randint(0, n - 1)

    if uf.sameset(u, v):
        continue

    uf.join(u, v)
    edges.add(tuple(sorted((u, v))))

while len(edges) < m:
    u: int = randint(0, n - 1)
    v: int = randint(0, n - 1)

    if u == v:
        continue

    edges.add(tuple(sorted((u, v))))

nedges: set = set()
for u, v in edges:
    if randint(0, 1):
        u, v = v, u

    u += 1
    v += 1

    nedges.add((u, v))

    adj[u].append(v)
    adj[v].append(u)

pipes = []
for edge in nedges:
    u, v = edge

    a = random.choice(adj[v])
    b = random.choice(adj[u])

    pipes.append((u, v, a, b))

s = randint(1, n)
r = randint(1, n)
while r == s:
    r = randint(1, n)

queries = []
for _ in range(q):
    # s = randint(1, n)
    # r = randint(1, n)
    t = randint(1, n)

    while s == r or s == t or r == t:
        # s = randint(1, n)
        # r = randint(1, n)
        t = randint(1, n)

    queries.append((s, r, t))

print(n, m, q)

for i in pipes:
    print(*i)

for i in queries:
    print(*i)
