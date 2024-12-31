#!/usr/bin/env python3

n = int(input())

while n != 0:
    # Do something
    if n == 1:
        print("{ }")
        n = int(input())

    num = bin(n - 1)[2:][::-1]
    print("{", end="")
    for idx, i in enumerate(num[:-1]):
        if i == "1":
            print(f" {3**idx},", end="")
    print(" " + str(3 ** (len(num) - 1)) + " }")
    n = int(input())
