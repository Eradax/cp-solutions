#!/usr/bin/env python3
import sys
sys.setrecursionlimit(int(5e5))

n, m, k = map(int, input().split())

d = {int(i) - 1 for i in input().split()}
g = [*map(int, input().split())]
p = [*map(int, input().split())]
r = {int(i) - 1 for i in input().split()}

maxel = max(d)

dp = [-1] * (maxel + 1)
def solve(day):
    if day > maxel:
        return 0

    if dp[day] != -1:
        return dp[day]

    ans = int(1e9)

    cheap = 2 if day in r else 1

    if day in d or cheap == 2:
        for gg, pp in zip(g, p):
            ans = min(ans, pp // cheap + solve(day + gg))
            for i in r:
                if day < i < day + gg:
                    ans = min(ans, pp // cheap + solve(i))

    if day not in d:
        ans = min(ans, solve(day + 1))

    dp[day] = ans
    return ans


print(solve(0))
