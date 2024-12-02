#!/usr/bin/env python3


def exclusive(A, zero, combine, node):
    n = len(A)
    exclusiveA = [zero] * n  # Exclusive segment tree

    # Build exclusive segment tree
    for bit in range(n.bit_length())[::-1]:
        for i in range(n)[::-1]:
            # Propagate values down the segment tree
            exclusiveA[i] = exclusiveA[i // 2]
        for i in range(n & ~int(bit == 0)):
            # Fold A[i] into exclusive segment tree
            ind = (i >> bit) ^ 1
            exclusiveA[ind] = combine(exclusiveA[ind], A[i], node, i)
    return exclusiveA


def rerooter(
    graph,
    default,
    combine,
    finalize=lambda nodeDP, node, eind: nodeDP,
):
    n = len(graph)
    rootDP = [0] * n
    forwardDP = [None] * n
    reverseDP = [None] * n

    # Compute DP for root=0
    DP = [0] * n
    bfs = [0]
    P = [0] * n
    for node in bfs:
        for nei in graph[node]:
            if P[node] != nei:
                P[nei] = node
                bfs.append(nei)

    for node in reversed(bfs):
        nodeDP = default[node]
        for eind, nei in enumerate(graph[node]):
            if P[node] != nei:
                nodeDP = combine(nodeDP, DP[nei], node, eind)
        DP[node] = finalize(
            nodeDP, node, graph[node].index(P[node]) if node else -1
        )
    # DP for root=0 done

    # Use the exclusive function to reroot
    for node in bfs:
        DP[P[node]] = DP[node]
        forwardDP[node] = [DP[nei] for nei in graph[node]]
        rerootDP = exclusive(
            forwardDP[node], default[node], combine, node
        )
        reverseDP[node] = [
            finalize(nodeDP, node, eind)
            for eind, nodeDP in enumerate(rerootDP)
        ]
        rootDP[node] = finalize(
            (
                combine(rerootDP[0], forwardDP[node][0], node, 0)
                if n > 1
                else default[node]
            ),
            node,
            -1,
        )
        for nei, dp in zip(graph[node], reverseDP[node]):
            DP[nei] = dp
    return rootDP, forwardDP, reverseDP


n = int(input())

p = [int(i) for i in input().split()]

adj = [[] for _ in range(n)]

for _ in range(n - 1):
    a, b = (int(i) - 1 for i in input().split())
    adj[a].append(b)
    adj[b].append(a)


def combine(nodeDP, neiDP, node, eind):
    return [nodeDP[0] + neiDP, max(nodeDP[1], neiDP)]


def finalize(nodeDP, node, eind):
    if eind == -1:
        return max(
            (nodeDP[0] + 1) // 2,
            p[node],
            nodeDP[1],
        )

    return max(nodeDP[0], p[node])


rootDP, forwardDP, backwardsDP = rerooter(
    adj, [[0, 0] for _ in range(n)], combine, finalize
)

ans = min(rootDP)

# print(f"{rootDP = }")
# print(f"{forwardDP = }")
# print(f"{backwardsDP = }")

print(ans)
