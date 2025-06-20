from math import floor
n = int(input())
x = [0] + [int(i) for i in input().split()]

for k in range(1, n):
    l = [x[k * i] for i in range(1, 1 + floor(n / k))]

    if len(l) < 2:
        break

    m = -1
    f = 1
    for i in l:
        f &= m < i
        m = i

    if f:
        print(k)
        exit()

print("ABORT!")
