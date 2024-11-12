#!/usr/bin/env python3

n,s = map(int,input().split())

trees = [[int(i)for i in input().split()]for _ in range(n)]

trees = sorted(trees, key=lambda x: x[-1])

curr = trees[-1][0]
speed = [trees[-1][1]]

for tree in trees[::-1][1:]:
    curr += tree[0]
    speed += [speed[-1]+tree[1]]

speed = speed[::-1]
speed += [0]

i = 0
sec = 0
while curr < s:
    nxtsec = trees[i][-1]
    if curr + (nxtsec - sec) * speed[i] <= s:
        curr += (nxtsec - sec) * speed[i]
        i+=1
        sec=nxtsec
        continue
    
    sec += (s-curr+speed[i]-1)//speed[i]
    break

print(sec)
