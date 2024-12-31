#!/usr/bin/env python3

F=input
D=int
G=D(F())
E,C='',0
for I in range(G):
    H,A,B=F().split();A,B=D(A)+1,D(B)
    if A*B>C:E,C=H,A*B
print(E,C)
