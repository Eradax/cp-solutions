#!/usr/bin/env python3
def ask(v):
    print("?", "".join(map(str, v)), flush=True)

    ret = [int(i) for i in input().strip()]

    # print(f"{ret = }")

    return ret


n = int(input())
nums = [(i, 0, n) for i in range(n)]

while any(lo + 1 < hi for _, lo, hi in nums):
    nums.sort(key=lambda x: x[1])

    # print(f"{nums = }")

    q = [0] * n
    for num in nums:
        _, lo, hi = num
        mi = (lo + hi) // 2
        for i in range(lo, mi):
            q[i] = 0
        for i in range(mi, hi):
            q[i] = 1

    ret = ask(q)

    nnums = []
    for i, lo, hi in nums:
        if ret[i]:
            lo = (lo + hi) // 2
        else:
            hi = (lo + hi) // 2

        nnums.append((i, lo, hi))

    nums = nnums

nums.sort(key=lambda x: x[0])

# print(f"{nums = }")

print("! ", end="")
for _, _, hi in nums:
    print(hi, end=" ")
print("", flush=True)
