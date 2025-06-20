n = int(input())
h = int(input())

pos = []
neg = []

for _ in range(n):
    x, y = map(int, input().split())

    if x < 0:
        neg.append((-x, y))
    if x > 0:
        pos.append((x, y))

pos.sort()
neg.sort()

ans = 0
ms = -1e18
for x, y in pos:
    sl = (y - h) / x

    if sl > ms:
        ms = sl
        ans += 1

ms = -1e18
for x, y in neg:
    sl = (y - h) / x

    if sl > ms:
        ms = sl
        ans += 1

print(ans)
