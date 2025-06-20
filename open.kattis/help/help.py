n = int(input())
while n:
    a = sorted(map(int, input().split()))

    for i in range(n):
        print(f"{a[-i]}-{'AB'[i % 2]}", end=" ")
    print()

    n = int(input())
