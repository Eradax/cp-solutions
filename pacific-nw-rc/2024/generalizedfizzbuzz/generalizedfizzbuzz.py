#!/usr/bin/env python3

n, a, b = map(int, input().split())

ff = bb = fb = 0

for i in range(1, n+1):
    ans = ""
    if (i % a == 0):
        ans += "Fizz"

    if (i % b == 0):
        ans += "Buzz"

    fb += ans == "FizzBuzz"
    bb += ans == "Buzz"
    ff += ans == "Fizz"

print(ff, bb, fb)
