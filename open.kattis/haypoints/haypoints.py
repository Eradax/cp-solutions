#!/usr/bin/env python3

m, n = map(int, input().split())
d = {}

for i in range(m):
    w, t = input().split()
    d[w] = int(t)

for _ in range(n):
    a = 0
    l = input()
    while l != '.':
        a += sum(d.get(i, 0) for i in l.split())
        l = input()
    print(a)


