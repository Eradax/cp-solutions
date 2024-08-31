n, q = [int(i) for i in input().split()]
arr = input().split()
pairs = len(arr)-len(set(arr))

if q+1 == 2*n:
    print(n)
elif q+2 == 2*n and pairs == q:
    print(n)
else:
    print(pairs)
