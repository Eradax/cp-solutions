#!/usr/bin/env python3

line = input()
ans = 2 * line.count(":)") + line.count("(:") - line.count("(:)")

print(ans)
