#!/usr/bin/env python3
import itertools
import string

MOD = int(1e9) + 7

n, m = map(int, input().split())

words = {input().strip() for _ in range(m)}

ans = 0

for w in itertools.product(string.ascii_lowercase, repeat=n):
    flag = False
    w = ''.join(w)
    for wo in words:
        if wo in w:
            flag = True
            break
    ans += not flag

print(ans % MOD)

