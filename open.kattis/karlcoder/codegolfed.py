#!/usr/bin/env python3

i=v=1
while v!=0:
    i+=1
    print(f'buf[{2**i-1}]')
    v=int(input())
l=2**(i-1)-1;r=2*l
while l!=r:
    m=(l+r)//2+(l+r)%2
    print(f'buf[{m}]')
    v=int(input())
    if v:
        l=m
    else:
        r=m-1
print(f'strlen(buf) = {l+1}')
