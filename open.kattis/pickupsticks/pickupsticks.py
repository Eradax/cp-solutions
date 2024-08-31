import sys
sys.setrecursionlimit(1000000)
n,m=map(int, input().split())
graph = [[]for _ in range(n)]

for _ in range(m):
	over, under = map(int, input().split())
	graph[under-1]+=[over-1]

top=[]
visited=[0]*n
stack=[0]*n
def dfs(v):
	visited[v] = 1
	stack[v] = 1

	for u in graph[v]:
		if not visited[u]:
			if dfs(u):
				return True
		elif stack[u]:
			return True
	
	top.append(v+1)
	stack[v] = 0
	return False


def main():
	for node in range(n):
		if not visited[node]:
			if dfs(node):
				print("IMPOSSIBLE")
				return

	print(*top, sep='\n')
main()