#!/usr/bin/env python3

class DSU:
	def __init__(self, n):
		self.rank = [1] * n
		self.size = [1] * n
		self.sets = n
		self.parent = [i for i in range(n)]
 
	def find(self, x):
		if (self.parent[x] != x):
			self.parent[x] = self.find(self.parent[x])
		return self.parent[x]

	def count(self, x):
		xset = self.find(x)
		xsize = self.count(xset)
		return xsize
 
	def Union(self, x, y):
		 
		# Find current sets of x and y
		xset = self.find(x)
		yset = self.find(y)
 
		# If they are already in same set
		if xset == yset:
			return
 
		# Put smaller ranked item under
		# bigger ranked item if ranks are
		# different
		self.sets -= 1
		if self.rank[xset] < self.rank[yset]:
			self.size[yset] += self.size[xset]
			self.parent[xset] = yset
 
		elif self.rank[xset] > self.rank[yset]:
			self.size[xset] += self.size[yset]
			self.parent[yset] = xset
 
		# If ranks are same, then move y under
		# x (doesn't matter which one goes where)
		# and increment rank of x's tree
		else:
			self.size[xset] += self.size[yset]
			self.parent[yset] = xset
			self.rank[xset] = self.rank[xset] + 1

def main():
	# N: number of rows
	# M: number of columns
	# K: number of classes
	n, m, k = map(int, input().split())

	board = zip(*[[*input()]for _ in' '*n])

	uf = DSU(k)
	for col in board:
		for i in range(n-1):
			uf.Union(ord(col[i])-ord('A'), ord(col[i+1])-ord('A'))
	print(uf.sets)

	

main()