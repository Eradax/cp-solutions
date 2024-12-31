#!/usr/bin/env python3
n=int(input())
c=0
while n:c+=1;r=int('1'*(len(str(n))));n-=r//((1,10)[r>n])
print(c)
