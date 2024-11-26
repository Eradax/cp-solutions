#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**6)
n,k=map(int,input().split())
nuts={int(i)-1 for i in input().split()}

adj=[[]for _ in range(n)]
for _ in range(n-1):
    a,b=[int(i)-1 for i in input().split()]

    adj[a]+=[b]
    adj[b]+=[a]

vis=[0]*n
def dfs(u):
    s = 0
    needed = 0

    if u in nuts:
        needed = 1

    vis[u]=1

    for v in adj[u]:
        if vis[v]:continue
        l, b = dfs(v)
        if b:
            s+=l+1
            needed = 1

    return s, needed

print(dfs(0)[0]*2)
