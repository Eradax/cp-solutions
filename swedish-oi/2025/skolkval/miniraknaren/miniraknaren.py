#!/usr/bin/env python3

n = int(input())
m = int(input())

t = 0
while n:
    k, j = divmod(n, m)

    if k == 1 and j > 0:
        n -= m - 1
        t += 1
        continue

    if j > 0:
        n -= j
        t += 1

    if n > 0:
        n //= m
        t += 1

print(t)
