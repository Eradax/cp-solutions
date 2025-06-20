#!/usr/bin/env python3
import itertools
from subprocess import run

gen = "./gen.py"
ans = "./ans.o"
sol = "./sol.o"

for i in itertools.count(1):
    if i % 100 == 0:
        print(f"{i = }")

    gend = run(
        [gen],
        capture_output=True,
        check=True,
    )

    ansd = run([ans], input=gend.stdout, capture_output=True)

    if ansd.returncode != 0:
        print("ANS crashed")
        print(gend.stdout.decode())
        break

    sold = run([sol], input=gend.stdout, capture_output=True)

    if sold.returncode != 0:
        print("SOL crashed")
        print(gend.stdout.decode())
        break

    ans_vals = [int(i) for i in ansd.stdout.decode().split()]
    sol_vals = [int(i) for i in sold.stdout.decode().split()]

    if ans_vals[0] != sol_vals[0]:
        print(f"Found diff after {i} iterations")
        print(gend.stdout.decode())
        print("--------------------")
        print(ansd.stdout.decode())
        print("--------------------")
        print(sold.stdout.decode())
        break
