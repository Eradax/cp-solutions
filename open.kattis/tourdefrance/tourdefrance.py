try:
    while True:
        f, r = [int(i) for i in input().split()]

        ff = [int(i) for i in input().split()]
        rr = [int(i) for i in input().split()]

        stuff = [i / j for i in rr for j in ff]

        stuff.sort()

        adj = [i / j for i, j in zip(stuff[1:], stuff)]

        print(f"{max(adj):.2f}")
except:
    ...