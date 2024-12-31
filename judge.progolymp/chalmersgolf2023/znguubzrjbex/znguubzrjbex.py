#!/usr/bin/env python3

a, b, c, s = map(int, input().split())
ans = []

for x in range(81):
    for y in range(81):
        for z in range(81):
            if a * x + b * y + c * z == s:
                ans.append(f"{x} {y} {z}")

if ans:
    print(*ans, sep="\n")
else:
    print("impossible")
