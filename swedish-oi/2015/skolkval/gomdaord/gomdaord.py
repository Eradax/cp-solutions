#!/usr/bin/env python3
def toVal(c):
    return ord(c)-64

word = input()
n = len(word)

ans = ""

i = 0


while i < n:
    #print(word[i])
    ans += word[i]
    i += toVal(word[i])


print(ans)

