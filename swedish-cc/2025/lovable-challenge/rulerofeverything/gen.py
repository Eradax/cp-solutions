#!/usr/bin/env python3
from random import randint

n_max = 1000
q_max = 1000
k_max = 1000
a_max = 1000
b_max = 1000

n = randint(1, n_max)
q = randint(1, q_max)

lines = [(randint(1, a_max), randint(1, b_max)) for _ in range(n)]
queries = [randint(1, k_max) for _ in range(q)]

print(n, q)
for i in lines:
    print(*i)
print(*queries)
