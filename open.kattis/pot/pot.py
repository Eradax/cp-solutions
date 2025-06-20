n = int(input())
print(sum([int(i[:-1])**int(i[-1]) for i in [input() for _ in range(n)]]))
