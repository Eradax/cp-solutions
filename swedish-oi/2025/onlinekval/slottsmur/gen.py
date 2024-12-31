#!/usr/bin/env python3
import random

N = 1000
Q = 1000
H_MAX = int(1e9)
# H_MAX = 10

Q1 = Q // 2
Q2 = Q - Q1

T = [1] * Q1 + [2] * Q2
random.shuffle(T)

n, q = N, Q
h = [random.randint(1, H_MAX) for _ in range(n)]

print(n, q)
print(*h)

for i in range(q):
    if T[i] == 1:
        l = random.randint(1, n - 1)
        r = random.randint(l + 1, n)

        print(T[i], l, r)
    else:
        ind = random.randint(1, n)
        
        while h[ind - 1] >= H_MAX:
            ind = random.randint(1, n)

        w = random.randint(1, H_MAX - h[ind - 1])

        h[ind - 1] += w

        print(T[i], ind, w)
