#!/usr/bin/env python3
from random import randint

n_max = 1 * 10**1
s_max = 1 * 10**1

assert n_max <= s_max

n = randint(1, n_max)
s = set()
while len(s) < n:
    s.add(randint(1, s_max))

print(n)
print(*s)
