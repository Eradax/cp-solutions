#!/usr/bin/env python3

M=filter
E=map
D=input
F=int(D())+1
G=D()
H,I=E(int,D().split())
N=lambda x:2*(x in'>v')-1
J,K=[*E(N,M(lambda x:x in'<>',G))],[*E(N,M(lambda x:x in'v^',G))]
def L(f,l,h):
    while l<h:
        m=(l+h)//2
        if f(m):h=m
        else:l=m+1
    return l
def A(n,i):
    A=0
    for B in i:A=max(0,min(A+B,n-1))
    return A
B=L(lambda x:A(x,J)>=I,1,F)
if A(B,J)!=I:B=0
C=L(lambda x:A(x,K)>=H,1,F)
if A(C,K)!=H:C=0
print(B*C if C and B else-1)
