#!/usr/bin/env python3

N = 1000000

tree = [0] * (4 * N)


def build(arr):
    for i in range(n):
        tree[n + i] = arr[i]

    for i in range(n - 1, 0, -1):
        tree[i] = tree[i << 1] + tree[i << 1 | 1]


def flip(p):
    tree[p + n] = 1 if tree[p + n] == 0 else 0
    p = p + n
    i = p
    while i > 1:
        tree[i >> 1] = tree[i] + tree[i ^ 1]
        i >>= 1


# function to get sum on interval [l, r)
def query(l, r):
    res = 0
    # loop to find the sum in the range
    l += n
    r += n
    while l < r:
        if l & 1:
            res += tree[l]
            l += 1

        if r & 1:
            r -= 1
            res += tree[r]

        l >>= 1
        r >>= 1

    return res


n, k = (int(i) for i in input().split())
ans = []

for _ in range(k):
    line = input().split()

    if line[0] == "F":
        flip(int(line[1]))
    else:
        ans.append(str(query(int(line[1]), int(line[2]) + 1)))

print(*ans, sep="\n")
