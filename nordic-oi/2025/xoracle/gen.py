#!/usr/bin/env python3
import sys
import random

MAXDEG = 3

def main():
    random.seed()

    N = random.randint(2, 10)
    Q = N - 1

    degrees = [0] * (N + 1)
    
    # for i in range(2, N + 1):
    #     parent = random.randint(1, i - 1)
    #     degrees[i] += 1
    #     degrees[parent] += 1

    while (sum(degrees)) < 2 * (N - 1):
        u = random.randint(1, N)
        while degrees[u] >= MAXDEG:
            u = random.randint(1, N)
        v = random.randint(1, N)
        while u == v or degrees[v] >= MAXDEG:
            u = random.randint(1, N)

        degrees[u] += 1
        degrees[v] += 1

    assert sum(degrees) == 2 * (N - 1)

    output = f"{N} {Q}" + "".join(f" {d}" for d in degrees[1:])
    print(output)

if __name__ == '__main__':
    main()
