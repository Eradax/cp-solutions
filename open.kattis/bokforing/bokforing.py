#!/usr/bin/env python3

n, q = [int(i) for i in input().split()]
ans = []

vals = [0]*n
epoch = [0]*n
res = 0
curr_epoch = 0

for day in range(q):
    action = input().split()

    if action[0] == "PRINT":
        if epoch[int(action[1])-1] == curr_epoch:
            ans.append(vals[int(action[1])-1])
            continue

        ans.append(res)

    if action[0] == "RESTART":
        curr_epoch += 1
        res = int(action[1])
        continue

    if action[0] == "SET":
        vals[int(action[1])-1] = int(action[2])
        epoch[int(action[1])-1] = curr_epoch


print(*[f"{i}\n" for i in ans])
