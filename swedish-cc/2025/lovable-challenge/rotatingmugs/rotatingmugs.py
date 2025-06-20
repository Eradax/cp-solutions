#!/usr/bin/env python3

m = int(input())
s = input()
ma = {
    'N': 0,
    'E': 1,
    'S': 2,
    'W': 3,
}

v = [ma[i] for i in s]

sr = sum(v)
mr = max(v)

if (m == 2):
    print(sr // 2 if v[0] == v[1] else -1)
elif sr % 2:
    print(-1)
elif mr <= sr // 2:
    print(sr // 2)
else:
    print(4)
