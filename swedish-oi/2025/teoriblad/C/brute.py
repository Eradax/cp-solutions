#!/usr/bin/env python3
from collections.abc import Generator


def all_pairs(v) -> Generator[list, None, None]:
    if len(v) < 2:
        yield []
        return
    if len(v) % 2 == 1:
        for i in range(len(v)):
            yield from all_pairs(v[:i] + v[i + 1 :])
    else:
        a = v[0]
        for i in range(1, len(v)):
            p = (a, v[i])
            yield from map(
                lambda x: [p] + x,
                all_pairs(v[1:i] + v[i + 1 :]),
            )


def solve(
    n: int, m: int, adj: list[list[int]], edges: list[tuple[int]]
) -> list:
    # print(f"{edges = }")

    for matching in all_pairs(edges):
        match_len = len(matching)
        flag = True
        for (u, v), (w, x) in matching:
            if len({u, v, w, x}) == 4:
                flag = False
                break
        if flag:
            return match_len, matching

    return 0, []


def get_input():
    n: int
    m: int
    n, m = map(int, input().split())

    adj: list[list[int]] = [[] for _ in range(n)]

    edges: list[tuple[int]] = []

    for _ in range(m):
        u, v = map(int, input().split())

        u -= 1
        v -= 1

        adj[u].append(v)
        adj[v].append(u)

        edges.append((u, v))

    return n, m, adj, edges


if __name__ == "__main__":
    inp = get_input()

    match_len, matching = solve(*inp)

    assert match_len == len(matching) == len(inp[3]) // 2

    print(f"{'Ans':-^72}")

    print(match_len)
    for e1, e2 in matching:
        print(f"{e1} --> {e2}")
