#!/usr/bin/env python3

n, q = map(int, input().split())

v = [int(i) for i in input().strip()]

for _ in range(q):
    t, l, r = map(int, input().split())
    if t == 1:
        for i in range(l, r + 1):
            v[i] ^= 1
    else:
        v[l : r + 1] = sorted(v[l : r + 1])

    best = 1
    l = 0
    r = 1

    while r < n:
        if v[l] == v[r]:
            r += 1
            best = max(best, r - l)
        else:
            l = r
            r = r + 1

    print(best)
