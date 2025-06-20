#!/usr/bin/env python3
from collections import defaultdict
import sys
n, k = map(int, input().split())
a = [int(i) for i in input().split()]

if k == 2:
    ma = 0.5
    for i in range(n - 1):
        if a[i] == a[i + 1]:
            ma = max(ma, 1)

    for i in range(n - 2):
        if a[i] == a[i + 2]:
            ma = max(ma, 2 / 3)

    print(ma)
    exit()

ma = 0
left = right = 0
for i in range(n - k + 1):
    cnts = defaultdict(int)
    curma = (-1, -1)
    for j in range(i, n):
        cur = a[j]
        cnts[cur] += 1

        if cnts[cur] > curma[1]:
            curma = (cur, cnts[cur])

        if (j - i + 1) >= k:
            if curma[1] / (j - i + 1) > ma:
                ma = curma[1] / (j - i + 1)
                left = i
                right = j

print(ma)
# print(left, right, file=sys.stderr)

