#!/usr/bin/env python3
input()
V=[0,0]
v=[0,0]
g=25
for i in input():
    v[i=='B']+=1;g=25-10*(sum(V)==2)
    if max(v)>=g and max(v)-min(v)>=2:V[v[1]>v[0]]+=1;v=[0,0]
print(*V)
