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

def gen(n_max: int, m_max: int, t_max: int, w_max: int, e_max: int):
    n: int = randint(2, n_max)
    m: int = randint(1, m_max)
    t: int = randint(1, t_max)


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

        w = randint(1, w_max)

        nedges.add((u, v, w))

    e = [randint(1, e_max) for _ in range(n-1)]

    rats = [randint(1, n-1) for _ in range(m)]

    return (n, m, t), nedges, e, rats



if __name__ == "__main__":
    (n, m, t), edges, e, rats = gen(100, 100, 100, 100, 100)
    print(n, m, t)

    for i in edges:
        print(*i)

    print(*e)
    print(*rats)
