from heapq import heappop, heappush


def dijkstra(graph, start):
    n = len(graph)
    dist, parents = [float("inf")] * n, [-1] * n
    dist[start] = 0

    queue = [(0, start)]
    while queue:
        path_len, v = heappop(queue)
        if path_len == dist[v]:
            for w, edge_len in graph[v]:
                if edge_len + path_len < dist[w]:
                    dist[w], parents[w] = edge_len + path_len, v
                    heappush(queue, (edge_len + path_len, w))

    return dist, parents

def main():
	n, m = map(int, input().split())

	g = [[] for _ in range(n)]

	for _ in range(m):
		a,b,c = map(int, input().split())

		g[a-1].append((b-1, c))
		g[b-1].append((a-1, c))

	print(dijkstra(g, 0)[0][-1])
main()