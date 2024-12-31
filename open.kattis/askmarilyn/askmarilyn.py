#!/usr/bin/env python3

import random

choices = {'A', 'B', 'C'}
for _ in range(1000):
    choice = random.choice(list(choices))

    print(choice)

    ret = input().split()

    if ret[1] == '1':
        print(ret[0])
    else:
        print("".join(choices - {choice, ret[0]}))

    input()
