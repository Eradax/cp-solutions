#!/usr/bin/env python3

import sys
sys.setrecursionlimit(10**6)

n,k = map(int,input().split())

times = [int(i) for i in input().split()]

dp = [[-1 for _ in range(k+1)] for _ in range(n+1)]

INF = 10**9

def time(i, b):
    if dp[i][b] != -1:
        return dp[i][b]

    if b <= 0:
        dp[i][b] = 0
        return 0
    if i >= n:
        dp[i][b] = INF
        return INF

    t1 = (b>1)+times[i]+time(i+1,b-1)
    t2 = 1+time(i+1,b)

    dp[i][b] = min(t1, t2)
    return dp[i][b]

# for i in range(n):
#     time(i, k)
time(0, k)

ans = INF
for i in dp:
    if i[k] >= 0:
        ans = min(i[k], ans)

# print("--------")
#
# for row in dp:
#     for v in row:
#         print(f"{v:<12}", end="")
#     print()
#
# print("--------")

print(ans)
