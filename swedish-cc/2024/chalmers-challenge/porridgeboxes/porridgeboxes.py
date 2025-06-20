#!/usr/bin/env python3
a, b, d, n = map(int, input().split())

days = set(map(int, input().split()))

lo = -1
hi = 10**9

while lo + 1 < hi:
    mi = lo + (hi - lo) // 2

    eaten = 0

    fr = 0
    day = 0

    while day < b:
        if day in days and fr + d - 1 <= mi:
            eaten += 1
            fr += d - 1
        elif fr:
            fr -= 1
            eaten += 1
        day += 1

    if eaten >= a:
        hi = mi
    else:
        lo = mi


if hi >= 10**9 - 10:
    print("impossible")
else:
    print(hi)
