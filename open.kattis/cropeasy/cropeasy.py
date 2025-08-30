t = int(input())

for i in range(t):
    n, A, B, C, D, x0, y0, M = map(int, input().split())
    X = x0
    Y = y0

    vals = []
    vals.append((X, Y))
    for j in range(n - 1):
        X = (A * X + B) % M
        Y = (C * Y + D) % M
        vals.append((X, Y))

    ans = 0

    for j in range(n - 2):
        for k in range(j + 1, n - 1):
            for w in range(k + 1, n):
                ans += all(sum(i) % 3 == 0 for i in zip(vals[j], vals[k], vals[w]))
    
    print(f"Case #{i + 1}: {ans}")