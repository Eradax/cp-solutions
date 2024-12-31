#!/usr/bin/env python3

inp = input()
last = ''
ans = ''

for i in inp:
    if not i == last:
        ans += i
    last = i
print(ans)
