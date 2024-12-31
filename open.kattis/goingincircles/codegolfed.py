#!/usr/bin/env python3

p='1010100'*9
k=""
i=0
m=input
a=print
while p!=k[-63:]:
 l=m();k+=l
 if i<63 and p[i]!=l:a("? flip");m()
 a("? right");i+=1
a("!",i-63)