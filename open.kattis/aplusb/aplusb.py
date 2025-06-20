#!/usr/bin/env python3
import sys
import math
import cmath

def fft(a, invert=False):
    n = len(a)
    j = 0
    # bit-reversal permutation
    for i in range(1, n):
        bit = n >> 1
        while j & bit:
            j ^= bit
            bit >>= 1
        j |= bit
        if i < j:
            a[i], a[j] = a[j], a[i]

    length = 2
    while length <= n:
        angle = 2 * math.pi / length * (-1 if invert else 1)
        wlen = cmath.rect(1, angle)  # e^(i*angle)
        for i in range(0, n, length):
            w = 1+0j
            for j in range(i, i + length // 2):
                u = a[j]
                v = a[j + length // 2] * w
                a[j] = u + v
                a[j + length // 2] = u - v
                w *= wlen
        length <<= 1

    if invert:
        # if inverse FFT, divide by n
        for i in range(n):
            a[i] /= n

def conv(a, b):
    if not a or not b:
        return []
    # result size
    res_sz = len(a) + len(b) - 1
    # next power of two
    n = 1 << ((res_sz - 1).bit_length())
    fa = [complex(val, 0) for val in a] + [0] * (n - len(a))
    fb = [complex(val, 0) for val in b] + [0] * (n - len(b))

    fft(fa, invert=False)
    fft(fb, invert=False)
    for i in range(n):
        fa[i] *= fb[i]
    fft(fa, invert=True)

    # take real parts and round
    return [fa[i].real for i in range(res_sz)]

data = sys.stdin.read().split()
it = iter(data)
n = int(next(it))

ADD = 50_000
MAXV = 100_001

a = [0.0] * MAXV
a2 = [0] * MAXV
zc = 0

for _ in range(n):
    v = int(next(it))
    if v == 0:
        zc += 1
    idx = v + ADD
    a[idx] += 1.0
    a2[idx] += 1

b = conv(a, a)
c = [int(round(x)) for x in b]

for i in range(len(a)):
    c[2 * i] -= a2[i]

ans = -zc * (n - 1) * 2

for i in range(len(a)):
    ans += a2[i] * c[i + ADD]

print(ans)
