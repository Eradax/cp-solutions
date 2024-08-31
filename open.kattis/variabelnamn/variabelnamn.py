from collections import defaultdict

n = int(input())
c = set()
nc = defaultdict(lambda:0)
for _ in '1'*n:
    cn = int(input())
    k = max(nc[cn], cn)
    while k in c:
        nc[k] = max(nc[k], 2*k)
        k+=cn
    nc[cn]=k+cn
    c.add(k)
    print(k)
