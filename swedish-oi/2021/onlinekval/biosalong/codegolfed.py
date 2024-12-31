#!/usr/bin/env python3
n,l=int(input()),input()
r=[i for i in range(n)if l[i]=='.']
print(min(a-b for a,b in zip(r[1:],r))-1)

