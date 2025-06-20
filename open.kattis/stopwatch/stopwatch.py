n = int(input())
if n%2:
    print("still running")
else:
    v=[int(input())for i in range(n)]
    print(sum(v[1::2]) - sum(v[::2]))
