#!/usr/bin/env python3

n, q = map(int, input().split())
h = [int(i) for i in input().split()]

for _ in range(q):
    t, l, r = map(int, input().split())

    if t == 1:
        l -= 1
        r -= 1

        rmq = (-1, -1)
        for i in range(l, r + 1):
            rmq = max(rmq, (h[i], i))
        mid = rmq[1]

        ans = 0
        m = 0
        for i in range(l, mid):
            m = max(m, h[i])
            ans += m - h[i]
        
        m = 0
        for i in range(mid + 1, r + 1)[::-1]:
            m = max(m, h[i])
            ans += m - h[i]

        print(ans)
    else:
        i = l - 1
        w = r

        h[i] += w
