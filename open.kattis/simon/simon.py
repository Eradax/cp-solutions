#!/usr/bin/env python3

n = int(input())

for _ in' '*n:
    inp = input()
    if inp[:10] == 'simon says':
        print(inp[11:])
    else:
        print()