#!/usr/bin/env python3
n,q=map(int,input().split())
d=[*map(int,input().split())]
p=sorted(zip(map(int,input().split()), range(q)))
a=[]
i=c=0
for I in range(n):
    c+=d[I]
    while i<q and p[i][0]<c:
        a+=[[p[i][1],I+1]]
        i+=1
while i<q:
    a+=[[p[i][1],-1]]
    i+=1
for i in sorted(a):
    print(i[1])

