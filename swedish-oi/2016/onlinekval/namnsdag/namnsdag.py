#!/usr/bin/env python3
q=input()
w={q[:i]+j+q[i+1:]for i in range(len(q))for j in"qwertyuiopasdfghjklzxcvbnm"if q[i]!=j}
r=int(input())
print(min([r]+[i+1 for i in range(r)if input()in w]))
