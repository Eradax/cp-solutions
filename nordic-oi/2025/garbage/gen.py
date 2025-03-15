#!/usr/bin/env python3
from random import randint

N = 1000
W = randint(1, 1000)
H = randint(1, 1000)

w_max = 1000

p = [(randint(0, 5 * W), randint(0, 5 * H), randint(1, w_max)) for _ in range(N)]

print(N, W, H)
for i in p:
    print(*i)
