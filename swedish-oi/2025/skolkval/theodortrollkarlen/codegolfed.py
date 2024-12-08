#!/usr/bin/env python3

M=10**9+7
n,k,s,a=map(int,input().split())
f=[1]*(n+k)
for i in range(1,n+k):f[i]=(f[i-1]*i)%M
def N(n,k):return(n>=k>=0)*f[n]*pow(f[k]*f[n-k],-1,M)
def S(u):return sum(pow(a*u,i,M)*pow(s,n-i,M)*N(n,i)*N(u,n-i)for i in range(n+1))
print((S(k)-S(k-1))%M)

