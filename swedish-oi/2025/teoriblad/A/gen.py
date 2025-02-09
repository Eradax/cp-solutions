#!/usr/bin/env python3
import random


def gen(max_n, max_r):
    n = random.randint(1, max_n)
    intervals = []
    for _ in range(n):
        l = random.randint(1, max_r - 1)
        r = random.randint(l, max_r)
        intervals.append((l, r))

    return n, intervals


if __name__ == "__main__":
    n, intv = gen(5, 10)
    
    print(n)
    for i in intv:
        print(*i)
