#!/usr/bin/env python3

import sys
input = sys.stdin.readline
print = sys.stdout.write

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
        self.num_sets = n

    def find(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def union(self, a, b):
        a, b = self.find(a), self.find(b)
        if a != b:
            if self.size[a] < self.size[b]:
                a, b = b, a

            self.num_sets -= 1
            self.parent[b] = a
            self.size[a] += self.size[b]

    def set_size(self, a):
        return self.size[self.find(a)]

    def __len__(self):
        return self.num_sets

def main():
	n, q = map(int, input().split())

	dsu = DSU(n)

	for _ in range(q):
		action, a, b = input().split()
		a, b = int(a), int(b)

		if action == '=':
			dsu.union(a, b)
		else:
			print("yes\n" if dsu.find(a) == dsu.find(b) else "no\n")
main()