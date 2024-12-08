#!/usr/bin/env python3

n,s,a=map(int,input().split())
H=[*map(int,input().split())]
l=0
h=2*10**10
while l<h:
    m=(l+h)//2
    if m>=sum((i-m*a+s-1)//s*(i>m*a)for i in H):h=m
    else:l=m+1
print(l)
