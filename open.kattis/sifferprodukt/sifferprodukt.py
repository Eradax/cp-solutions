num = int(input())
while num >= 10:
    c = 1
    while num:
        c = max(c, c * (num % 10))
        num //= 10

    num = c

print(num)
