#!/usr/bin/env python3
import sys
import time
from typing import Any

ct = time.time_ns

s = ct()
indata = {}
for i in sys.stdin:
    num, line = i.split(' ', 1)
    indata[int(num)] = line

e = ct()
print(f"read inp: {e - s}", file=sys.stderr)
s = ct()

# print(f"{indata = }")

lines: list[int] = sorted(indata.keys())
# print(f"{lines = }")

to_i = dict(zip(lines, range(len(lines))))

pdata = [(indata[i].split(' ', 1)[0], (indata[i].split(' ', 1)[1] if indata[i].split(' ', 1)[0][0] == "P" else indata[i].split(' ', 1)[1].split())) for i in lines]


ndata: list[Any] = []
for l in lines:
    d = indata[l]

    op, line = d.split(' ', 1)

    if op == "LET":
        line = line.split()

        if len(line) > 3:
            ndata.append((0, line))
        else:
            ndata.append((1, line))
    elif op == "PRINT":
        ndata.append((2, line))
    elif op == "PRINTLN":
        ndata.append((3, line))
    else:
        c1, c2, c3, _, _, nl = line.split()
        nl = int(nl)
        ndata.append((4, (c1, c2, c3, nl)))
    


vars = [0] * 29


e = ct()

print(f"process inp: {e - s}", file=sys.stderr)
s = ct()

i = 0
while i < len(lines):
    op, line = pdata[i]

    if op == "LET":
        if len(line) > 3:
            # print(f"{vars[ord(vals[2][0]) - ord('A')] if ord(vals[2][0]) > 57 else vals[2]}{vals[3] if vals[3] != '/' else '//'}{vars[ord(vals[4][0]) - ord('A')] if ord(vals[4][0]) > 57 else vals[4]}")

            v1: int = (vars[ord(line[2][0]) - ord('A')] if ord(line[2][0]) > 57 else int(line[2]))
            v2: int = (vars[ord(line[4][0]) - ord('A')] if ord(line[4][0]) > 57 else int(line[4]))

            res: int
            if line[3] == '+':
                res = ((v1 + v2) + 2**31) % 2**32 - 2**31

            elif line[3] == '-':
                res = ((v1 - v2) + 2**31) % 2**32 - 2**31

            elif line[3] == '*':
                res = ((v1 * v2) + 2**31) % 2**32 - 2**31

            else:
                res = v1 // v2 + (((v1<0)^(v2<0))&((v1%v2) != 0))

        else:
            res = vars[ord(line[2][0]) - ord('A')] if ord(line[2][0]) > 57 else int(line[2])
        
        # print(f"{res = }")

        vars[ord(line[0]) - ord('A')] = res

    elif op[0] == "P":
        if line[0] == "\"":
            _ = sys.stdout.write(line[1:-2] + '\n'*(op[-1]=="N"))
        else:
            _ = sys.stdout.write(str(vars[ord(line[0]) - ord('A')]) + '\n'*(op[-1]=="N"))

    else:
        ni = to_i[int(line[-1])]

        c1 = (vars[ord(line[0][0]) - ord('A')] if ord(line[0][0]) > 57 else int(line[0]))
        c2 = (vars[ord(line[2][0]) - ord('A')] if ord(line[2][0]) > 57 else int(line[2]))

        if line[1] == "=": 
            if c1 == c2:
                i = ni
                continue
        elif line[1] == "<>": 
            if c1 != c2:
                i = ni
                continue
        elif line[1] == "<": 
            if c1 < c2:
                i = ni
                continue
        elif line[1] == ">": 
            if c1 > c2:
                i = ni
                continue
        elif line[1] == "<=": 
            if c1 <= c2:
                i = ni
                continue
        else: 
            if c1 >= c2:
                i = ni
                continue

    i += 1

e = ct()

print(f"running code: {e - s}", file=sys.stderr)
