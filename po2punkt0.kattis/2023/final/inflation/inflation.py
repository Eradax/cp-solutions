#!/usr/bin/env python3
I = float(input())

nums = [float(i) for i in input().split()]

for num in nums:
    I = max(I+num, I*(1+num/100))

print(f"{I}")

