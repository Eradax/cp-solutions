#!/usr/bin/env python3

A=lambda:input().split()
n,m=A()
h,c={A()[0]},set()
for _ in' '*int(m):
    a,_,b=A()
    if(a in h)-1:c|={a}
    h-={a};h|={b}
print(len(c))
print(*sorted(c))
