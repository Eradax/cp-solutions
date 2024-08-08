#!/usr/bin/env python3

n: int
q: int

n, q = map(int, input().split())

arr = [int(i) for i in input().split()]

for _ in range(q):
    l: int
    r: int
    v: int

    l, r, v = map(int, input().split())

    sor: list[int] = sorted(arr[l:r+1])

    s: int = 0
    idx: int = 0
    while s <= v and idx < len(sor):
        s += sor[idx]
        idx += 1

    print(len(sor) if sum(sor) <= v else idx-1)
