#!/usr/bin/env python3


def find(a, f, v):
    if v not in a[f[v - 1]]:
        print(f"{a = }")
        print(f"{f = }")
        print(f"{v = }")
        exit(1)

    return f[v - 1]
    # for i, aa in enumerate(a, start=0):
    #     if v in aa:
    #         assert f[v - 1] == i
    #         return i


def solve():
    n, m = map(int, input().split())

    a = [
        {
            i,
        }
        for i in range(1, n + 1)
    ]

    f = [i - 1 for i in range(1, n + 1)]
    s = [i for i in range(1, n + 1)]

    for _ in range(m):
        line = [*map(int, input().split())]
        if line[0] == 1:
            _, p, q = line

            pg = find(a, f, p)
            qg = find(a, f, q)

            if pg == qg:
                continue

            if len(a[pg]) > len(a[qg]):
                pg, qg = qg, pg

            for i in a[pg]:
                a[qg].add(i)
                f[i - 1] = qg
                s[qg] += i

            a[pg].clear()
            s[pg] = 0

        elif line[0] == 2:
            _, p, q = line

            pg = find(a, f, p)
            qg = find(a, f, q)

            if pg == qg:
                continue

            a[pg].remove(p)
            a[qg].add(p)
            f[p - 1] = qg
            s[pg] -= p
            s[qg] += p
        else:
            _, p = line
            pg = find(a, f, p)

            print(len(a[pg]), s[pg])

try:
    while True:
        solve()
except:
    ...
