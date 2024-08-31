import sys
input = sys.stdin.readline
n, m = map(int, input().split())

while n+m != 0:
	jack = [int(input()) for _ in range(n)]
	jill = [int(input()) for _ in range(m)]

	ans = 0
	ja = ji = 0
	while ja < n and ji < m:
		if jack[ja] == jill[ji]:
			ans+=1
			ja += 1
			ji += 1
		elif jack[ja] > jill[ji]:
			ji += 1
		else:
			ja += 1
	print(ans)
	n,m=map(int,input().split())