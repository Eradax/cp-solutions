#!/usr/bin/env python3
from subprocess import run
from itertools import count

gen = "./gen.py"
ans = "./ans.o"
sol = "./sol.o"

for i in count(1):
    if i % 100 == 0:
        print(f"{i = }")

    gend = run([gen], capture_output=True, check=True)
    ansd = run([ans], capture_output=True, check=True, input=gend.stdout)

    sold = run([sol], capture_output=True, input=gend.stdout)

    if sold.returncode != 0:
        print("SOL crashed!!!!!")
        print("GEN")
        print(gend.stdout.decode())
        print("ANS")
        print(ansd.stdout.decode())

        break

    ansvals = [int(i) for i in ansd.stdout.decode().split()]
    solvals = [int(i) for i in sold.stdout.decode().split()]

    if ansvals != solvals:
        print("FOUND DIFF")
        print("GEN")
        print(gend.stdout.decode())
        print("ANS")
        print(ansd.stdout.decode())
        print("SOL")
        print(sold.stdout.decode())

        break
