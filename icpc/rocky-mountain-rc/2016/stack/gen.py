#!/usr/bin/env python3
from random import randint, choices

T = 1
LEN = 10
ALPH = "abc"

t = randint(1, T)
print(t)

for _ in range(t):
    l = randint(1, LEN)
        
    line = ''.join(choices(ALPH, k=l))

    print(line)
