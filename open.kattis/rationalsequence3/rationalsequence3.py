def solve(n):
	path = []
	while n != 1:
		path.append(n%2)
		n //= 2

	p, q = 1, 1
	for val in reversed(path):
		if val:
			p, q = p+q, q
		else:
			p, q = p, q+p

	return p, q

def main():
	p = int(input())

	for _ in range(p):
		m, n = map(int, input().split())
		p, q = solve(n)

		print(f"{m} {p}/{q}")

main()