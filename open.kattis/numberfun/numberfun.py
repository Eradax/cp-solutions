#!/usr/bin/env python3

n = int(input())

for i in range(n):
    a,b,c=map(int,input().split())

    if (a+b==c or a*b==c or a/b==c or a-b==c or b/a==c or b-a==c):
        print("Possible")
    else:
        print("Impossible")
