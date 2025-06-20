c = int(input())

for cc in range(c):
    s = input()
    t = input()

    if s.count('1') > t.count('1'):
        print(f"Case {cc + 1}: -1")
        continue

    ans = s.count('?')

    f = [0, 0]

    for i, j in zip(s, t):
        if i == '?':
            continue

        if i != j:
            f[int(i)] += 1

    ans += max(f)

    print(f"Case {cc + 1}: {ans}")
