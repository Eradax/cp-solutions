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


def gen(
    n_max: int, m_max: int, gen_tree: bool = False
) -> list[set[tuple[int]]]:
    assert n_max - 1 <= m_max <= n_max * (n_max - 1) // 2

    n: int = randint(2, n_max)
    m: int = randint(n - 1, m_max)

    if gen_tree:
        m = n - 1

    while not n - 1 <= m <= n * (n - 1) // 2:
        n = randint(2, n_max)
        m = randint(n - 1, m_max)

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

    for _ in range(m - len(edges)):
        u: int = randint(0, n - 2)
        v: int = randint(u + 1, n - 1)

        while (u, v) in edges:
            u = randint(0, n - 2)
            v = randint(u + 1, n - 1)

        edges.add(tuple(sorted((u, v))))

    nedges: set = set()

    for u, v in edges:
        if randint(0, 1):
            u, v = v, u

        u += 1
        v += 1

        nedges.add((u, v))

        # print(u, v)

    return (n, m), nedges


if __name__ == "__main__":
    (n, m), edges = gen(5, 10, True)
    print(n, m)
    for u, v in edges:
        print(u, v)
