#!/usr/bin/env python3
n,k,h,*v=map(int,open(0).read().split()) 
L,H=0,9**20
while L<H:
    M=L+H>>1;g=M;p=1
    for i in v:g-=max(0,i*h-g*(k-1));p&=g>=0
    if p:H=M
    else:L=M+1
print(L)
