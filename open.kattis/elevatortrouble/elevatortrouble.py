def layers(n, up, down, goal, start=0):
	used = [False] * (n+1)
	used[start] = True
	q = [start]
	depth = 0
	while q:
		if used[goal]:
			return depth
		depth += 1
		nq = []
		for v in q:
			for w in filter(lambda x: 1<=x<=n, [v+up, v-down]):
				if not used[w]:
					used[w] = True
					nq.append(w)
		q = nq
	return "use the stairs"

		



def main():
	f: int
	s: int
	g: int
	u: int
	d: int

	f, s, g, u, d = map(int, input().split())
	print(layers(f, u, d, g, s))

main()