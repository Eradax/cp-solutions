prim = 9113823
mod = 10**9 + 7

def rhash(s, l):
    n = len(s)
    if l > n:
        return set()

    h = 0
    hp = pow(prim, l, mod)

    for i in range(l):
        h = (h * prim + ord(s[i])) % mod

    hh = {h}
    for i in range(l, n):
        h = (h * prim - ord(s[i-l]) * hp + ord(s[i])) % mod
        hh.add(h)

    return hh


def lcs(strs):
    strs.sort(key=len)
    lo, hi = 0, len(strs[0])
    best = 0
    while lo <= hi:
        mid = (lo + hi) // 2
        ah = rhash(strs[0], mid)
        if not ah:
            hi = mid - 1
            continue

        for s in strs[1:]:
            hset = rhash(s, mid)
            ah &= hset
            if not ah:
                break

        if ah:
            best = mid
            lo = mid + 1
        else:
            hi = mid - 1

    return best

n = int(input())
v = [input().strip() for _ in range(n)]
print(lcs(v))
