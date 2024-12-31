#!/usr/bin/env python3
from heapq import heappop, heappush

DBG = 0

n, m, q = map(int, input().split())

adj = [[] for _ in range(n)]

for _ in range(m):
    u, v, s = map(int, input().split())

    u -= 1
    v -= 1

    adj[u].append([v, s])
    adj[v].append([u, s])

for _ in range(q):
    a, b, f, k, l = map(int, input().split())

    a -= 1
    b -= 1

    start = a

    dist, parents = [float("inf")] * n, [-1] * n
    dist[start] = 0

    queue = [(0, start)]
    while queue:
        path_len, v = heappop(queue)
        if path_len == dist[v]:
            for w, edge_len in adj[v]:
                if max(edge_len, path_len) < dist[w]:
                    dist[w], parents[w] = max(edge_len, path_len), v
                    heappush(queue, (max(edge_len, path_len), w))

    ans = 0
    if DBG: print(f"{dist[b] = }")
    for i in range(f):
        ans += (k * i + l) >= dist[b]

    print(ans)
