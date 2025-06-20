n = int(input())
d = []

v1 = 2.4589042467268095
v2 = 10**-9

for _ in range(2 * n):
    a, b = map(int, input().split())
    d.append([a, b])

d.sort(key=lambda x: x[1] - x[0]*v1)

m = d[n-1][1] - d[n - 1][0] * v1 + v2

print(v1, m)
