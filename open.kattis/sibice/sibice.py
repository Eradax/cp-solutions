n, w, h = map(int, input().split())
l = (w**2 + h**2)**.5
for _ in range(n):
    print("DA" if int(input()) <= l else "NE")
