#!/usr/bin/env python3

a=input
b,c,d=(int(i)for i in a().split())
e=lambda x:[x]if x==1 else e(1+(x-2)//c)+[x]
for J in range(d):h,l=(int(i)for i in a().split());f,g=e(h),e(l);print(len(f)+len(g)-2*sum([i==j for(i,j)in zip(f,g)]))
