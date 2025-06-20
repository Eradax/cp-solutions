from math import ceil
a, i = map(float, input().split())

lo = 0
hi = 1e10

while lo + 1 < hi:
    mi = (lo + hi) // 2

    if ceil(mi / a) >= i:
        hi = mi
    else:
        lo = mi

print(round(hi))
