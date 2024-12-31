#!/usr/bin/env python3

n, s, m = [int(i) for i in input().split()]
vals = [int(i) for i in input().split()]
visited = [False] * n

h = 0

while 1 <= s <= n:
    if vals[s - 1] == m:
        print("magic")
        print(h)
        exit()

    if visited[s - 1]:
        print("cycle")
        print(h)
        exit()

    visited[s - 1] = True
    s += vals[s - 1]
    h += 1

if s < 1:
    print("left")
    print(h)
    exit()

print("right")
print(h)
