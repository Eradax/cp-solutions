#!/usr/bin/env python3

n=input()
c=v=sum(map(int,n))
I=A=0
for i in range(len(n)-1):a=min(c-1,9);c-=a;I+=a*10**i;a=min(v,9);A=A*10+a;v-=a
I+=c*10**(len(n)-1)
A=A*10+v
print(I,A)

