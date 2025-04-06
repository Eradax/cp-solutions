#!/usr/bin/env python3
import random
from random import randint
# random.seed(234567)

N = int(1e3)
MAXA = int(1e12)

n = randint(N, N)
a = [randint(1, MAXA) for _ in range(n)]

print(n)
print(*a)
