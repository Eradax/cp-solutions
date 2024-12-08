#!/usr/bin/env python3

n=int(input());m=int(input())
t=0
while n>0:
    if n<2*m:n-=m-1
    else:t+=n%m>0;n/=m
    t+=1
print(t)
