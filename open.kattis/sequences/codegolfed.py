#!/usr/bin/env python3

D=10**9+7
A=0
E=0
B=0
Q='1'
for C in input():F=C>Q;E+=C==Q;A+=A*F+(C!=Q)*(B+2*E)*pow(2,B-1,D);A%=D;B+=F
print(A)