a=sorted(map(int,input().split()))
print(*[a[ord(c)-65]for c in input()])
