a, b = map(int, input().split())

cnt = 0
while a != b:
    if b > a:
        cnt += b - a
        a = b
    else:
        cnt += 1 + (a % 2)
        a = (a + 1) // 2

print(cnt)
