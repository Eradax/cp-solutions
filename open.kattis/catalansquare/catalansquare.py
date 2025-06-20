n = int(input())

c = [0] * (n + 10)
c[0] = 1

for i in range(0, n + 1):
    c[i + 1] = c[i] * (4 * i + 2) // (i + 2)

print(c[n + 1])
