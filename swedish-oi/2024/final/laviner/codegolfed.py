#!/usr/bin/env python3

n,k,*P=map(int,open(0).read().split())
P=[0]+P
l,h=0,n
def D(m):
	c,S=0,[1]*n
	for i in range(n)[::-1]:c+=(S[i]>m);S[P[i]-1]+=S[i]*(S[i]<=m)
	return c
while h>l:m=(l+h)//2;(l:=m+1)if D(m)>k else(h:=m)
print(l)