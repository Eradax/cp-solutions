xs = []
ys = []
for _ in range(3):
    a, b = map(int, input().split())
    xs.append(a)
    ys.append(b)

print(sorted(xs, key=lambda x: xs.count(x))[0], sorted(ys, key=lambda x: ys.count(x))[0])
