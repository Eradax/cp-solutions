#!/usr/bin/env python3

def solve(p, q):
	# Right Child
	layers = 0
	if p == q:
		return p, q+p
	elif p > q:
		layers = (p-1)//q

		p, q = p - (q * layers), q

		if q > p:
			p, q = p, q-p

			p, q = p+q, q

			p, q = p, q + p * layers

		else:
			p, q = p, q * (layers+2)

	else:
		p, q = q, q-p

	return p, q


def main():
	n = int(input())

	for _ in range(n):
		m, f = input().split()
		p, q = map(int, f.split('/'))
		p, q = solve(p, q)
		print(f"{m} {p}/{q}")

main()