p, h, t = map(int, input().split())
print(max(0, (t - p - h) // max(p, h)) + (t - p - h >= 0))

