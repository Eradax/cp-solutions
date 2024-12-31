#!/usr/bin/env python3
import subprocess
import itertools

gen = "./gen.py"
ans = "./brute.py"
sol = "./liftkarta"

for round in itertools.count(1):
    if round % 100 == 0:
        print(f"{round = }")

    gen_data = subprocess.run(
        [gen],
        capture_output=True,
        text=True,
        check=True,
    )


    ans_data = subprocess.run(
        [ans],
        input=gen_data.stdout,
        capture_output=True,
        text=True,
        check=True,
    )


    sol_data = subprocess.run(
        [sol],
        input=gen_data.stdout,
        capture_output=True,
        text=True,
        check=True,
    )


    ans_vals = [int(i) for i in ans_data.stdout.split()]
    sol_vals = [int(i) for i in sol_data.stdout.split()]

    if ans_vals != sol_vals:
        print("----------- Found diffrence ----------")
        print("Gen:")
        print(gen_data.stdout)

        print("Ans:")
        print(ans_data.stdout)

        print("Sol:")
        print(sol_data.stdout)

        break
