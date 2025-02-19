#!/usr/bin/env python3
from random import choices, randint

N = 1
M = 2
Q = 1
D = 100

PER_QUICKSAND = 10
PER_CHANGE = 50
PER_IMP = 50
PER_RAND = 50

n = randint(1, N)
m = randint(1, M)
q = randint(1, Q)
d = randint(1, D)

while n * m > 3e5:
    n = randint(1, N)
    m = randint(1, M)

grid = [[-1] * m for _ in range(n)]
vis = [[0] * m for _ in range(n)]
quicksand = [
    [choices([1, 0], [PER_QUICKSAND, 100 - PER_QUICKSAND])[0] for _ in range(m)]
    for _ in range(n)
]

# for i in quicksand:
#     print(*i)

start = (randint(0, n - 1), randint(0, m - 1))
if choices([0, 1], [PER_RAND, 100 - PER_RAND]) == 0:
    for i in range(n):
        for j in range(m):
            grid[i][j] = randint(-1, d)
            while grid[i][j] == 0:
                grid[i][j] = randint(-1, d)

    grid[start[0]][start[1]] = 0

else:
    grid[start[0]][start[1]] = 0
    vis[start[0]][start[1]] = 1
    curr = [start]
    nxt = []
    dist = 0
    while len(curr):
        nxt = []
        dist += 1
        for r, c in curr:
            for dr, dc in [[0, 1], [0, -1], [1, 0], [-1, 0]]:
                nr = r + dr
                nc = c + dc
                if not (0 <= nr < n and 0 <= nc < m):
                    continue

                if vis[nr][nc]:
                    continue
                vis[nr][nc] = 1
                grid[nr][nc] = dist

                if quicksand[nr][nc] == 0:
                    nxt.append((nr, nc))

        curr = nxt


print(n, m, q)
for i in grid:
    print(*i)

opts = "?!"
for _ in range(q):
    op = choices([1, 0], [PER_CHANGE, 100 - PER_CHANGE])[0]
    if op == 0:
        r = randint(1, n)
        c = randint(1, m)
        print(opts[op], r, c)
    else:
        r = randint(1, n)
        c = randint(1, m)
        dd = choices(range(-1, d + 1), [PER_IMP, 0, *([(100 - PER_IMP) / d] * d)])[0]

        print(opts[op], r, c, dd)
