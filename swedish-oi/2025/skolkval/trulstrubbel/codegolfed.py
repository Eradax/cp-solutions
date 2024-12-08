#!/usr/bin/env python3
a=[0,0]
for i in input():
    a[i<'T']+=1
    if(max(a)>=11)&(abs(a[0]-a[1])>1):a=[0,0]
print(*a,sep='-')

