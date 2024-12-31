#!/usr/bin/env python3

from collections import defaultdict
def main():
	"""
	2-pointer
	Have a dict to keep track of how many times we have seen things
	"""

	n: int = int(input())
	word = [input()for _ in' '*n]

	if n == 1:
		print(0)
		return

	l = 0
	r = 1
	seen = defaultdict(lambda: 0)
	best = 1_000_000
	seen[word[0]] += 1
	while r < n:
		if seen[word[r]] > 0:
			while seen[word[r]] > 0:
				seen[word[l]] -= 1
				l+=1
			best = min(best, r-l+1)
		seen[word[r]] += 1
		r += 1

	print(max(0, n - best))
main()