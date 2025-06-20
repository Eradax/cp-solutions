#!/usr/bin/env python3
n = int(input())
nums = [(i, 0, n) for i in range(n)]
for _ in range(10):
    nums.sort(key=lambda x: x[1])
    q = [0] * n
    for _, lo, hi in nums:
        for i in range(lo, hi):
            q[i] = i >= (lo + hi) / 2

    print("?", "".join(map(str, q)), flush=True)
    ret = input()

    nnums = []
    for i, lo, hi in nums:
        if ret[i]:
            lo = (lo + hi) // 2
        else:
            hi = (lo + hi) // 2
        nnums.append((i, lo, hi))
    nums = nnums
nums.sort(key=lambda x: x[0])

print("! ", end="")
for _, _, hi in nums:
    print(hi, end=" ")
print("", flush=True)
