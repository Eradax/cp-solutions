#!/usr/bin/env python3
line = input()

T = 0
H = 0
for i in line:
    T += i == "T"
    H += i == "H"

    if abs(T - H) >= 2 and max(T, H) >= 11:
        T = 0
        H = 0

print(f"{T}-{H}")
