#!/usr/bin/env python3
from random import choices, randint
from string import ascii_lowercase as alph


def f(k, N, r, cap=10**12 + 1):
    if r == 0:
        return N

    if r == 1:
        res = N + k * (N - 1)
        return res if res < cap else cap

    def pow_capped(base, exp):
        result = 1
        while exp:
            if exp & 1:
                result *= base
                if result >= cap:
                    return cap
            exp //= 2
            if exp:
                base *= base
                if base >= cap:
                    base = cap
        return result

    rpow = pow_capped(r, k)

    second = (N - r) * (rpow - 1) // (r - 1)

    total = rpow * N + second
    return total if total < cap else cap


inc = '#include "main.hpp"'
other = ("aaaaa", "defregt", "gdsf")

N = int(100)
K = int(100)
Q = int(100)

n = randint(4, N)
k = randint(1, K)
q = randint(1, Q)

incs = 2

print(n, k, q)

a = randint(1, n - 3)
b = n - 2 - a

for _ in range(a):
    print("".join(choices(alph, k=10)))

print(inc)

for _ in range(b):
    print(other[randint(0, len(other) - 1)])

print(inc)

max_p = min(f(k, n, incs), int(1e12))

for _ in range(q):
    print(randint(1, max_p))
