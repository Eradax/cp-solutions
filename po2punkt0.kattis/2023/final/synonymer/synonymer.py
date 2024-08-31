#!/usr/bin/env python3
from collections import defaultdict
n = int(input())
g = defaultdict(set)

for _ in range(n):
    a, b = input().split()

    g[a].add(b)
    g[b].add(a)

m = int(input())
words = input().split()
for word in words:
    middleWords = g[word]
    newWords = []
    for middleWord in middleWords:
        newWords.extend(g[middleWord])

    tmp = list(set(newWords)-{word})
    if tmp: 
        print(tmp[0], end=" ")
    else:
        print(word, end=' ')
print()

