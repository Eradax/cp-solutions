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


def gen(n_max: int, k_max: int, s_max: int):
    n: int = randint(2, n_max)
    k: int = randint(1, k_max)

    n = n_max
    k = k_max

    t_max = d_max = s_max

    uf: UF = UF(n)

    # print(n, m)

    edges: set = set()
    while len(edges) < n - 1:
        u: int = randint(0, n - 1)
        v: int = randint(0, n - 1)

        if uf.sameset(u, v):
            continue

        uf.join(u, v)
        edges.add(tuple(sorted((u, v))))

    nedges: set = set()
    for u, v in edges:
        if randint(0, 1):
            u, v = v, u

        w = randint(1, s_max)

        u += 1
        v += 1

        nedges.add((u, v, w))

        # print(u, v)

    trains = []
    for _ in range(k):
        u = randint(1, n)
        v = randint(1, n)
        while u == v:
            v = randint(1, n)
        t = randint(1, t_max)
        d = randint(1, d_max)

        trains.append((u, v, t, d))

    return (n, k), nedges, trains


if __name__ == "__main__":
    (n, k), edges, trains = gen(3, 2, 2)
    print(n, k)
    for i in edges:
        print(*i)

    for i in trains:
        print(*i)
