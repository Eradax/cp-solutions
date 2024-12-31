#!/usr/bin/env python3

def lcs(w1: str, w2: str):
    if w1.startswith(w2) or w2.startswith(w1):
        return 0

    n = 0
    for i,j in zip(w1,w2):
        if i!=j: break
        n+=1

    return n

def solve():
    n = int(input())
    arr = sorted([input()[::-1] for _ in range(n)])
    #print(arr)
    l = 0

    for i in range(n-1):
        l = max(l, lcs(arr[i], arr[i+1]))

    print(l)
solve()
