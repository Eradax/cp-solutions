lo = 0
hi = 1001

while lo + 1 < hi:
    mi = (lo + hi) // 2

    print(mi, flush=True)
    s = input()

    if s == "correct":
        exit()

    if s == "higher":
        lo = mi
    else:
        hi = mi

