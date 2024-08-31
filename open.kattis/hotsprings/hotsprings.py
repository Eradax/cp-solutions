input();a=sorted(int(i)for i in input().split());k=0
for _ in a:print(a[len(a)//2+k],end=' ');k=-k-int(k>=0)
