p = int(input())

for _ in range(p):
    k, b, n = map(int, input().split())

    ans = 0
    while n:
        ans += (n % b)**2
        n //= b

    print(k, ans)
