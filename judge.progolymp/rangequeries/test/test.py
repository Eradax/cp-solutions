#!/usr/bin/env python3
import os

inp = "./inp.txt"
ans = "./ans.txt"
out = "./out.txt"

for i in range(int(1e2)):
    print(f"------ Starting TC {i} -------")
    os.system(f"./gen.py {i} > {inp}")
    os.system(f"./sol.py < {inp} > {ans}")
    os.system(f"./a.out < {inp} > {out}")

    if open(ans, 'r').read() != open(out, 'r').read():
        print(f"****** Failed on TC {i} ********")
        exit()
