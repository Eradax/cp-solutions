#!/usr/bin/env python3

n = int(input())
names = [input() for _ in range(n)]

fnames = []

for i in names:
    if len(set(i)) == len(i) and len(i) >= 5:
        fnames.append(i)

numMin = 30
shortnames = []
for i in fnames:
    if len(i) < numMin:
        numMin = len(i)
        shortnames = [i]
    elif len(i) == numMin:
        shortnames.append(i)

if shortnames:
    print(sorted(shortnames)[-1])
else:
    print("Neibb")
