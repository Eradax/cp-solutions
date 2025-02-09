#!/usr/bin/env python3
import itertools


def solve(
    n: int, m: int, adj: list[list[int]], edges: list[tuple[int]]
) -> list:
    def solve_tree(
        u: int, p: int
    ) -> tuple[list[tuple[tuple[int]]], bool]:
        ans = list(itertools.batched(adj[u], 2))

        if len(adj[u]) % 2 == 1:
            ans = ans[:-1]

            if p != -1:
                ans.append((adj[u][-1], (u, p)))

        edges_left = []
        for v in adj[u]:
            if v == p:
                continue

            matchings, used_last = solve_tree(v, u)
            ans += matchings
            if not used_last:
                edges_left.append((u, v))

        edge_pairs_add = list(itertools.batched(edges_left, 2))
        if len(edges_left) % 2 == 1:
            edge_pairs_add = edge_pairs_add[:-1]
            if p != -1:
                edge_pairs_add.append((edges_left[-1], (u, p)))

        ans += edge_pairs_add

        return ans, len(edges_left) % 2 == 1

    ans, _ = solve_tree(0, -1)

    return len(ans), ans


def get_input(
    n: int = 0,
    m: int = 0,
    edges: set[tuple[int]] | None = None,
    term: bool = True,
):
    if term:
        edges = set()
        n, m = map(int, input().split())

        for _ in range(m):
            u, v = map(int, input().split())
            edges.add((u, v))

    adj: list[list[int]] = [[] for _ in range(n)]

    nedges: list[tuple[int]] = []

    for u, v in edges:
        u -= 1
        v -= 1

        adj[u].append(v)
        adj[v].append(u)

        nedges.append((u, v))

    for i in range(n):
        adj[i].sort(reverse=True)

    return n, m, adj, nedges


if __name__ == "__main__":
    inp = get_input()

    match_len, matching = solve(*inp)

    print(f"{match_len=}")
    print(f"{matching=}")

    print(f"{'Ans':-^72}")

    print(match_len)
    for e1, e2 in matching:
        print(f"{e1} <--> {e2}")

    assert match_len == len(matching) == len(inp[3]) // 2
