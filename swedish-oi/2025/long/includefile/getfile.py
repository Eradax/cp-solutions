#!/usr/bin/env python3
import sys

input = sys.stdin.read().split("\n")
ptr = 0

fl = input[ptr].strip().split()
n = int(fl[0])
k = int(fl[1])
q = int(fl[2])
ptr += 1

og = []
for _ in range(n):
    l = input[ptr].strip()
    og.append(l)
    ptr += 1

for _ in range(q):
    ptr += 1

exp = {}
exp[k] = og.copy()

for m in range(k - 1, -1, -1):
    cexp = []
    for l in og:
        if l == '#include "main.hpp"':
            cexp.extend(exp.get(m + 1, og.copy()))
        else:
            cexp.append(l)
    exp[m] = cexp

ex = exp.get(0, og.copy())

print("\n----------------\n")

for l in ex:
    print(l)

print()
print(len(ex))
