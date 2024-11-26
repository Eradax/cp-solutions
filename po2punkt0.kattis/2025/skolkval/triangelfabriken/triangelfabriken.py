#!/usr/bin/env python3
v = [int(input()) for _ in range(3)]

if max(v) > 90:
    print("Trubbig Triangel")
elif 90 in v:
    print("Rätvinklig Triangel")
else:
    print("Spetsig Triangel")
