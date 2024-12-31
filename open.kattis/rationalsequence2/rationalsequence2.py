#!/usr/bin/env python3

def solve(p, q):
	path = []
	while p != q:
		if p > q:
			path.append(1)
			p, q = p-q, q
		else:
			path.append(0)
			p, q = p, q-p

	ans = 1
	for val in reversed(path):
		ans *= 2
		ans += val

	return ans

def main():
	n = int(input())

	for _ in range(n):
		m, f = input().split()
		p, q = map(int, f.split('/'))
		ans = solve(p, q)
		print(f"{m} {ans}")

main()