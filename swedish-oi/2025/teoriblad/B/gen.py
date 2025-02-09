#!/usr/bin/env python3
from random import randint, shuffle


def gen(n_max: int) -> list[int, list[int]]:
    assert n_max >= 1

    n: int = randint(1, n_max)

    arr = []

    fst = list(range(1, n + 1))
    shuffle(fst)

    arr.append(fst)

    for _ in range(2):
        row = [randint(1, n) for _ in range(n)]
        arr.append(row)

    return n, arr


if __name__ == "__main__":
    n, arr = gen(5, 10, True)

    print(n)
    for r in arr:
        print(*r)

