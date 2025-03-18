#!/usr/bin/env python3
from random import randint
from heapq import heappop, heappush

N = 2000
Q = 4000

used_p = set()
edge_set = set()
edges = []
q = []

cnt = 0
while cnt < Q:
    match randint(0, 2):
        case 0:
            edge = tuple(sorted((randint(1, N), randint(1, N))))
            if edge in edge_set or edge[0] == edge[1]:
                continue

            i = randint(1, N**2)
            if i in used_p:
                i = randint(1, N**2)

            heappush(edges, (-i, edge))
            edge_set.add(edge)
            used_p.add(i)

            q.append(("a", edge[0], edge[1], i))
        case 1:
            if len(edges) == 0:
                continue
            q.append("r")
            i, edge = heappop(edges)
            used_p.remove(-i)
            edge_set.remove(edge)
        case 2:
            q.append("d")

    cnt += 1

print(N, Q)
for i in q:
    print(*i)
