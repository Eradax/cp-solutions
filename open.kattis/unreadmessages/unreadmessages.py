from collections import defaultdict
n, m = map(int, input().split())

c = 0
d = defaultdict(lambda: -1)
a = 0

for _ in range(m):
    i = int(input())

    # print("---------")
    # print(f"{d = }")
    # print(f"{c = }")

    a += n - 1
    a -= c - d[i] - 1

    d[i] = c
    c += 1

    print(a)
