#!/usr/bin/env python3
import random

N = int(1e5)
R = int(1e6)

n = random.randint(1, N)

points = set()

while len(points) < 2 * n:
    points.add((random.randint(0, R), random.randint(0, R)))

print(n)
for p in points:
    print(*p)
