#!/usr/bin/env python3

N = input()
l = len(N)
n = int(N)
s = sum(int(i) for i in N)

ma = 0
sc = s
for _ in range(l):
    a = min(sc, 9)
    sc -= a
    ma *= 10
    ma += a

MI = [int(i) for i in str(ma)][::-1]
if MI[0] == 0:
    MI[0] = 1

    i = 1
    while MI[i] == 0:
        i += 1

    MI[i] -= 1

mi = 0
for i in MI:
    mi *= 10
    mi += i

print(mi, ma)
