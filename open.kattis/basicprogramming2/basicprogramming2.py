#!/usr/bin/env python3

from collections import Counter
n, t = map(int, input().split())
v = [int(i) for i in input().split()]

match t:
    case 1:
        s = set()
        b = 0
        for i in v:
            if 7777 - i in s:
                print("Yes")
                b = 1
                break
            s.add(i)
        if b == 0:
            print("No")
    case 2:
        print("Unique" if len(v) == len(set(v)) else "Contains duplicate")
    case 3:
        v = Counter(v)
        a = sorted(v.items(), key=lambda x: x[1], reverse=True)
        print(a[0][0] if a[0][1] > n // 2 else -1)
    case 4:
        v = sorted(v)
        if n % 2:
            print(v[n // 2])
        else:
            print(v[n // 2 - 1], v[n // 2])
    case 5:
        print(*sorted(filter(lambda x: 100 <= x and x <= 999, v)))
