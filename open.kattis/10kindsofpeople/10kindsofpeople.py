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

    r, c = [int(i) for i in input().split()]

    grid = [list(input()) for _ in range(r)]
    
    graph = DSU(r*c)

    for x in range(c-1):
        for y in range(r-1):
            if grid[y][x] == grid[y][x+1]:
                graph.Union(x+y*c, x+1+y*c)
            if grid[y][x] == grid[y+1][x]:
                graph.Union(x+y*c, x+(y+1)*c)

    for x in range(c-1):
        if grid[r-1][x] == grid[r-1][x+1]:
            graph.Union(x+(r-1)*c, x+1+(r-1)*c)
    
    for y in range(r-1):
        if grid[y][c-1] == grid[y+1][c-1]:
            graph.Union(c-1+(y)*c, c-1+(y+1)*c) 

    n = int(input())
    
    ans = []
    for _ in range(n):
        y1, x1, y2, x2 = [int(i)-1 for i in input().split()]
        
        f1 = graph.find(x1+y1*c)
        f2 = graph.find(x2+y2*c)
        
        if f1 == f2:
            ans.append("decimal" if grid[y1][x1]=='1' else "binary")
        else:
            ans.append("neither")
    
    for l in ans:
        print(l)

if __name__ == "__main__":
    main()
