#!/usr/bin/env python3
from random import randint


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


def gen(n_max: int, k_max: int, q_max: int):
    n: int = randint(2, n_max)
    k = randint(1, k_max)
    q = randint(1, q_max)

    uf: UF = UF(n)

    # print(n, m)

    edges: set = set()
    while len(edges) < n - 1:
        u: int = randint(0, n - 1)
        v: int = randint(0, n - 1)

        if uf.sameset(u, v):
            continue

        uf.join(u, v)
        edges.add(tuple(sorted((u + 1, v + 1))))

    tracks = []
    while len(tracks) < k:
        u = randint(1, n)
        v = randint(1, n)

        while u == v:
            v = randint(1, n)

        tracks.append((u, v))

    queries = []
    for _ in range(q):
        a = randint(1, n)
        b = randint(1, n)

        while a == b:
            b = randint(1, n)

        queries.append((a, b))

    return (n, k, q), edges, tracks, queries


if __name__ == "__main__":
    (n, k, q), edges, tracks, queries = gen(1000, 1000, 1000)

    print(n, k, q)
    for edge in edges:
        print(*edge)

    for track in tracks:
        print(*track)

    for query in queries:
        print(*query)
