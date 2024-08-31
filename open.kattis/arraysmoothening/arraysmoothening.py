from collections import defaultdict as dd
from heapq import heapify, heappop, heappush

n, k = map(int, input().split())

arr = [int(i) for i in input().split()]

times = dd(int)

for i in arr:
	times[i] += 1

count = [-i for i in times.values()]
heapify(count)

for i in range(k):
	tmp = heappop(count)
	heappush(count, tmp+1)

print(-heappop(count))
