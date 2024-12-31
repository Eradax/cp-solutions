#!/usr/bin/env python3
import random

N = 5
M = 4
Q = 5
S = 100

F = 5
K = 10
L = 20

n, m, q, s = N, M, Q, S

print(n, m, q)

SG, TG = set(range(n)), set()
edges = set()

current_node = random.sample(sorted(SG), 1).pop()
SG.remove(current_node)
TG.add(current_node)

graph = [[] for _ in range(n)]

while SG:
    neighbor_node = random.sample(range(n), 1).pop()

    if neighbor_node not in TG:
        edge = (current_node, neighbor_node)
        graph[current_node] += [neighbor_node]
        graph[neighbor_node] += graph[current_node]

        SG.remove(neighbor_node)
        TG.add(neighbor_node)
        edges.add(tuple(sorted({current_node, neighbor_node})))
 
        # FIX: This generates a line, you should be able to move the
        # following line one step down but for some reason that makes
        # it such that the algorithm doesn't always create connected
        # trees
        current_node = neighbor_node

for _ in range(M - len(edges)):
    u = random.randint(0, n - 2)
    v = random.randint(u + 1, n - 1)

    while {u, v} in edges:
        u = random.randint(0, n - 2)
        v = random.randint(u + 1, n - 1)

    graph[u] += [v]
    graph[v] += [u]

    edges.add(tuple(sorted({u, v})))

for u, v in edges:
    if random.randint(0, 1):
        u, v = v, u

    u += 1
    v += 1

    ss = random.randint(1, s)

    print(u, v, ss)


queried_edges = set()

for _ in range(q):
    a = random.randint(1, n - 1)
    b = random.randint(a + 1, n)

    while (a, b) in queried_edges:
        a = random.randint(1, n - 1)
        b = random.randint(a + 1, n)

    queried_edges |= {(a, b)}

    f = random.randint(1, F)
    k = random.randint(1, K)
    l = random.randint(1, L)

    print(a, b, f, k, l)
