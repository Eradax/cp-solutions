#!/usr/bin/env python3
from random import randint

def gen(n_max: int, r_max: int, c_max: int, k_max: int):
    n: int = randint(1, n_max)

    squares = []

    for i in range(n):
        r = randint(1, r_max)
        c = randint(1, r_max)

        k = randint(1, k_max)

        squares.append((r, c, k))

    return n, squares


if __name__ == "__main__":
    n, rect = gen(100, 100, 100, 100)
    print(n)
    for i in rect:
        print(*i)
