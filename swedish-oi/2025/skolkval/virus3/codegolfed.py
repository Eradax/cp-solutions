#!/usr/bin/env python3

f,h=map(input,"  ")
F=len(f)
i=j=0
while(i<F)&(j<len(h)):i+=f[i]==h[j];j+=1
print("NJeaj"[i==F::2])

