#!/usr/bin/env python3
word = input()
k = int(input())

import string

ans = 100
for c in string.ascii_lowercase:
    i = 0
    cnt = 0
    while i < len(word):
        if word[i] != c:
            cnt += 1
            i += k
        else:
            i += 1
    ans = min(ans, cnt)
print(ans)

