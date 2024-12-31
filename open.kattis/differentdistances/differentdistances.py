#!/usr/bin/env python3

l = input()

while l != '0':
    x, y, xx, yy, p = map(float, l.split())

    print((abs(x - xx)**p + abs(y - yy)**p)**(1/p))

    l = input()
