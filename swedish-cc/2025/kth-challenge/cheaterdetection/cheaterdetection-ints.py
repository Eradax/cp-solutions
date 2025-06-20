#!/usr/bin/env python3
_, *vs = map(lambda x : int(float(x)*100 + .5), open(0).read().split())
for x in vs:
    cnt = x * 2 // 3

    if (cnt * 3 // 2 == x or (cnt + 1) * 3 // 2 == x):
        print("VALID")
    else:
        print("IMPOSSIBLE")
