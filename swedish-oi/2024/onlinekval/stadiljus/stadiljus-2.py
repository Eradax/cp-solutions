n = int(input())
x = int(input())
y = int(input())

l = sorted([int(i) for i in input().split()])

ans = 0
tc = 0
tl = 0

for i in l:
    if (tc + x * i) / (ans + 1) <= y:
        tc += x * i
        tl += i
        ans += 1

print(ans)
