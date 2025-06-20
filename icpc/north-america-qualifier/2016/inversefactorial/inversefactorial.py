#!/usr/bin/env python3
from math import log10

fac = input()

if len(fac) <= 9:
    fac = int(fac)
    n = 1
    nf = 1
    while nf < fac:
        n += 1
        nf *= n

    print(n)

    exit()

l10 = len(fac) - 1

val = 0
n = 1

while val < l10:
    n += 1
    val += log10(n)

print(n)
