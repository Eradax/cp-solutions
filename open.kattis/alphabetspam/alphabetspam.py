#!/usr/bin/env python3

inp = input()
und, low, upp, sym = 0, 0, 0, 0

for i in inp:
    if i == '_':
        und += 1
    elif i.islower():
        low += 1
    elif i.isupper():
        upp += 1
    else:
        sym += 1

print(und/len(inp))
print(low/len(inp))
print(upp/len(inp))
print(sym/len(inp))
