#!/usr/bin/env python3
import subprocess
import itertools

gen = "./gen.py"
ans = "./brute.py"
sol = "./sol.o"

for i in itertools.count(1):
    if i % 100 == 0:
        print(f"{i = }")

    gen_data = subprocess.run(
        [gen],
        capture_output=True
    ).stdout

    # print(f"{gen_data = }")

    ans_data = subprocess.run(
        [ans],
        input=gen_data,
        capture_output=True
    )

    sol_data = subprocess.run(
        [sol],
        input=gen_data,
        capture_output=True
    )

    ans_vals = [*map(int, ans_data.stdout.split())]
    sol_vals = [*map(int, sol_data.stdout.split())]

    if ans_vals != sol_vals:
        print("found diff")
        print("------GEN-----")
        print(gen_data.decode())
        print("------ANS------")
        print(ans_vals)
        print("------SOL------")
        print(sol_vals)

        break
