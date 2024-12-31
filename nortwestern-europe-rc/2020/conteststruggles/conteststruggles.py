#!/usr/bin/env python3

n, k, d, s = map(int, open(0).read().split())

ans = (n * d - k * s) / (n - k)

if 0 <= ans <= 100:
    print(ans)
else:
    print("impossible")
