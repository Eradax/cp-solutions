#!/usr/bin/env python3
def main():
    n, t, s = map(int, input().split())

    adl = []
    adr = []
    for _ in range(n):
        a, b = map(int, input().split())

        adl.append(a)
        adr.append(b)
    n+=1
    adl.append(t)
    adr.append(t)
    prefixSum = [0]
    for i in range(0, n):
        prefixSum.append(prefixSum[i] + adr[i]-adl[i])

    best = 0
    for idx, ad in enumerate(adl):
        # Find ad
        adV = prefixSum[idx]
        # Find ad+s
        sI = bSearch(lambda x: adl[x]>ad+s-1, 0, n-1)

        if adr[sI-1] > ad+s:
            sV = prefixSum[sI]-(adr[sI-1]-(ad+s))
        else:
            sV = prefixSum[sI]
        # Get diffrence
        adL = sV-adV
        # Update best
        best = max(best, adL)
        # Repeat

    print(s - best)


def bSearch(func, lo, hi):
    """ Locate the first value x s.t. func(x) = True within [lo, hi] """
    while lo < hi:
        mi = lo + (hi - lo) // 2
        if func(mi):
            hi = mi
        else:
            lo = mi + 1

    return lo

main()

