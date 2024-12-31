#!/usr/bin/env python3

M=10**9+7
n,k,s,a=map(int,input().split())
f=[1]*(n+k)
for i in range(1,n+k):f[i]=(f[i-1]*i)%M
def S(u):return sum(pow(a*u,i,M)*pow(s,n-i,M)*f[n]*f[u]*pow(f[i]*f[n-i]*f[n-i]*f[u-n+i],-1,M)for i in range(max(0,n-u),n+1))
print((S(k)-S(k-1))%M)

