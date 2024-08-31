from collections import defaultdict
import sys

sys.setrecursionlimit(10000000)

n, k, m = [int(i) for i in input().split()]

graph = defaultdict(set)

for i in range(m):
    v, w = [int(i) for i in input().split()]
    graph[v].add(w)
    graph[w].add(v)

visited = set()
def solve(start, parent):
    for next in graph[start] - visited - {parent}:
        visited.add(next)
        solve(next, start)

    #print(f"Start: {start}\nVisited:\n{visited}")

solve(k, k)
if k in visited:
    print('NO')
else:
    print('YES')
