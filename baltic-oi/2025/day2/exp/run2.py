#!/usr/bin/env python3
from subprocess import run
from itertools import count
from pathlib import Path
from tqdm import tqdm

gen = "./gen.py"
ans = "./ans.o"
sol = "./sol.o"

filed = Path("/home/eradax/Downloads/tests/")

for idx, path in tqdm(enumerate(filed.glob("exp*.in"))):
    gend = path.read_bytes()
    ansd = (filed / (path.stem + ".out")).read_bytes()
    sold = run([sol], capture_output=True, input=gend)

    # print(path)
    # print(idx)

    if sold.returncode != 0:
        print("SOL crashed!!!!!")
        print("GEN")
        print(gend.decode())
        print("ANS")
        print(ansd.decode())

        break

    ansvals = [int(i) for i in ansd.decode().split()]
    solvals = [int(i) for i in sold.stdout.decode().split()]

    if ansvals != solvals:
        print("FOUND DIFF")
        print("GEN")
        print(gend.decode())
        print("ANS")
        print(ansd.decode())
        print("SOL")
        print(sold.stdout.decode())

        break
