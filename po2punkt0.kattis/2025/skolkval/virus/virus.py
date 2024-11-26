#!/usr/bin/env python3

F = input()
H = input()

f = len(F)
h = len(H)

i = 0
j = 0

while i < f and j < h:
    i += F[i] == H[j]
    j += 1

print("Ja" if i == f else "Nej")
