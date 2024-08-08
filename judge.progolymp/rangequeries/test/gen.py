#!/usr/bin/env python3
import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

MAX_VAL: int = int(1e9)
MAX_N: int = int(1e4)
MAX_Q: int = int(1e2)

n: int = int(cmdlinearg("n", random.randint(1, MAX_N)))
q: int = int(cmdlinearg("q", random.randint(1, MAX_Q)))

print(n, q)

# arr = random.sample(range(0, MAX_VAL+1), n)
arr = [random.randint(1, MAX_VAL) for _ in range(n)]

print(*arr)

for i in range(q):
    l: int = random.randint(0, n-1)
    r: int = random.randint(l, n-1)
    v: int = random.randint(0, MAX_VAL)

    print(l, r, v)

print()
