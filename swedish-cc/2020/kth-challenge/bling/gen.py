#!/usr/bin/env python3
from random import randint

D = 5
B = 0
F = 10
T = 10

d = randint(1, D)
b = randint(0, B)
f = randint(0, F)
ft = (randint(0, T) for _ in range(3))

print(d, b, f, *ft)
