#!/usr/bin/env python3

n, m = map(int, input().split())

while not n==0:
	adj = [[]for _ in range(n)]
	for _ in range(m):
		u, v = map(int, input().split())
		adj[u]+=[v]
		adj[v]+=[u]

	timer = 0
	visited = [0]*n
	tin = [0]*n
	low = [0]*n

	def IS_BRIDGE():
		IS_BRIDGE.ans = "Yes"
	IS_BRIDGE.ans = "No"

	def dfs(v, p = -1):
		global timer
		visited[v] = True
		timer += 1
		tin[v] = low[v] = timer
		for to in adj[v]:
			if to == p:
				continue
			if visited[to]:
				low[v] = min(low[v], tin[to])
			else:
				dfs(to, v)
				low[v] = min(low[v], low[to])
				if low[to] > tin[v]:
					# We found a bridge
					IS_BRIDGE()

	def find_bridges():
		for i in range(n):
			if not visited[i]:
				dfs(i)

	find_bridges()
	print(IS_BRIDGE.ans)

	n, m = map(int, input().split())