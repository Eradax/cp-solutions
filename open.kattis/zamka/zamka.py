l = int(input())
d = int(input())
x = int(input())

for i in range(l, d+1):
    if sum(map(int, str(i))) == x:
        print(i)
        break


for i in range(l, d+1)[::-1]:
    if sum(map(int, str(i))) == x:
        print(i)
        break
