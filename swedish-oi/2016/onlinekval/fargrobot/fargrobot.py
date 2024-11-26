#!/usr/bin/env python3
n=int(input())
l=input()
i=0
for _ in' '*n:V=[l.find(a,i)for a in"RGB"];i=max(V)+1;print("RGB"[(i-1 in V[1:])+(i-1==V[2])],end="")
