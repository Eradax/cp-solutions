n = int(input())
x = int(input())
y = int(input())
lengths = sorted([int(i) for i in input().split()])

def binarySearch(lengths, l, r, y):
    k = (l+r)//2

    while l<=r:
        k = (l+r)//2

        if x*sum(lengths[:k]) <= y*k and x*sum(lengths[:k+1]) > y*(k+1):
            #print(x*sum(lengths[:k])/k)
            #print(x*sum(lengths[:k+1])/(k+1))
            return k

        if x*sum(lengths[:k]) > y*k:
            r = k-1
        else:
            l = k+1
    return n

print(binarySearch(lengths, 0, n, y))
