#!/usr/bin/env python3

n=int(input())
P=print
P(f"+{'-'*n}+")
[P(f"|{' '*n}|")for _ in' '*n]
P(f"+{'-'*n}+")