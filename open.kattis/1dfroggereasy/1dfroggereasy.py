n, s, m = [int(i) for i in input().split()]
vals = [int(i) for i in input().split()]
visited = [False]*n
def main(n, s, m):
    h=0
    while 1 <= s <= n:
        if vals[s-1] == m:
            print("magic")
            print(h)
            return
        if visited[s-1]:
            print("cycle")
            print(h)
            return
        visited[s-1] = True
        s += vals[s-1]
        h += 1
    if s < 1:
        print("left")
        print(h)
        return
    print("right")
    print(h)
main(n,s,m)
