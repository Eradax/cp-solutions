#!/usr/bin/env python3
import random
from string import ascii_lowercase

N = 3
M = 2

words = set()
while len(words) < M:
    word = "".join(
        random.choices(ascii_lowercase, k=random.randint(1, N))
    )
    words.add(word)

print(N, M)
print(*words, sep='\n')
