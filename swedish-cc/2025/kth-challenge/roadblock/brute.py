from collections import deque
import sys
input = sys.stdin.readline

n, m = [int(i) for i in input().split()]
x = [int(i) for i in input().split()]


edgs = []
adj = [set() for _ in range(n)]

for _ in range(m):
    u, v = [int(i) for i in input().split()]
    u -= 1
    v -= 1

    adj[u].add(v)
    adj[v].add(u)

    edgs.append((u, v))


def get_shortest_paths():
    ans = [1e9] * n
    vis = [0] * n
    q = deque()
    vis[0] = 1

    q.append((0, 0))

    while q:
        u, w = q.popleft()
        ans[u] = w

        for v in adj[u]:
            if vis[v] == 1:
                continue
            vis[v] = 1
            q.append((v, w + 1))

    return ans


mins = get_shortest_paths()

# print(f"{mins =}")

for i in range(m):
    u, v = edgs[i]

    adj[u].remove(v)
    adj[v].remove(u)

    cur = get_shortest_paths()

    # print(f"{cur = }")

    ans = 0
    for i in range(n):
        if cur[i] > mins[i]:
            ans += x[i]

    print(ans)

    adj[u].add(v)
    adj[v].add(u)
