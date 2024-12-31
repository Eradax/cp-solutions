#!/usr/bin/env python3

def main():
	n = int(input())

	remebered = {}

	for _ in range(n):
		name, like, date = input().split()

		like=int(like)
		if date in remebered and remebered[date][1]>like:
			pass
		else:
			remebered[date] = (name, like)

	print(len(remebered))
	print(*sorted([i[0] for i in remebered.values()]), sep='\n')
main()