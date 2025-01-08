#!/usr/bin/env python3
from itertools import combinations as combs

n, c = map(int, input().split())
d, s = zip(*(map(int, input().split()) for _ in range(n)))

for l in range(n + 1)[::-1]:
    for comb in combs(range(n), l):
        comb = sorted(comb, key=lambda x: s[x] - d[x])

        success = True
        size = 0
        for e in comb:
            if size + max(d[e], s[e]) > c:
                success = False
            size += s[e]

        if success:
            print(l)
            print(*(i + 1 for i in comb))
            exit()
