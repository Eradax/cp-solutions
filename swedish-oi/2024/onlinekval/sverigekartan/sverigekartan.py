#!/usr/bin/env python3
class DSU:
    def __init__(self, n):
        self.rank = [1] * n
        self.size = [1] * n
        self.parent = [i for i in range(n)]
 
    def find(self, x):
        if (self.parent[x] != x):
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def count(self, x):
        xset = self.find(x)
        xsize = self.size[xset]
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
    ans = []

    r, c, u = [int(input()) for _ in range(3)]
    sy, sx = 0, 0

    grid = []
    for rdx in range(r):
        row = []
        for cdx, i in enumerate(input()):
            if i == 'S':
                sy, sx = (rdx, cdx)
                row.append(True)
                continue
            row.append(i == '#')
        grid.append(row)
    
    graph = DSU(r*c)

    for x in range(c-1):
        for y in range(r-1):
            if grid[y][x] and grid[y][x+1]:
                graph.Union(x+y*c, x+1+y*c)
            if grid[y][x] and grid[y+1][x]:
                graph.Union(x+y*c, x+(y+1)*c)

    for x in range(c-1):
        if grid[r-1][x] and grid[r-1][x+1]:
            graph.Union(x+(r-1)*c, x+1+(r-1)*c)
    
    for y in range(r-1):
        if grid[y][c-1] and grid[y+1][c-1]:
            graph.Union(c-1+(y)*c, c-1+(y+1)*c) 

    ans.append(graph.count(sx+sy*c))

    for _ in range(u):
        y, x = [int(i)-1 for i in input().split()]
        grid[y][x] = True

        if x != c-1 and grid[y][x+1]:
            graph.Union(x+y*c, x+1+y*c)
        if x != 0 and grid[y][x-1]:
            graph.Union(x+y*c, x-1+y*c)
        if y != r-1 and grid[y+1][x]:
            graph.Union(x+y*c, x+c+y*c)
        if y != 0 and grid[y-1][x]:
            graph.Union(x+y*c, x-c+y*c)

        ans.append(graph.count(sx+sy*c))

    for i in ans:
        print(i)

if __name__ == "__main__":
    main()

