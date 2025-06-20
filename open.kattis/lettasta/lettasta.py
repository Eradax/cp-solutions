n = int(input())
m = int(input())

prob = input().split()
scores = [sum(i) for i in zip(*[[int(i) for i in input().split()] for _ in range(m)])]

print(max(zip(scores, prob))[1])
