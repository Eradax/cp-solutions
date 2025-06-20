from collections import Counter
n = int(input())
v = []
for i in range(n):
    input()
    v.append(input())

v = Counter(v)
for i in v:
    print(i, v[i])
