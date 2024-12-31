#!/usr/bin/env python3

n = int(input())

ans = 0
k = 6

while k < n:
	ans += 1

	k = (ans+1)*(ans+2)*(ans+3)

print(ans)