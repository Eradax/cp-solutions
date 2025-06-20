n = int(input())


s = []
b = []

for i in range(n):
    a, c = map(int, input().split())
    s.append(a)
    b.append(c)

r = [s[0]]
pref = b[0]

for i in range(n - 1):
    r.append(max(r[i], s[i + 1] - pref))
    pref += b[i + 1]

q = int(input())
for _ in range(q):
    st = int(input())

    lo = -1
    hi = n

    while lo + 1 < hi:
        mi = (lo + hi) // 2
        if r[mi] > st:
            hi = mi
        else:
            lo = mi

    print(lo + 1)
