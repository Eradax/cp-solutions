n = int(input())

res = []
for i in range(n):
    s = [int(i) for i in input().split()]
    for j in range(n):
        if s[j] != -1:
            res += [(i + 1, j + 1, s[j])]

print(len(res))
for i in res:
    print(*i)
