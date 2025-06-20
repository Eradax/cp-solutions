#!/usr/bin/env python3
import subprocess
import itertools

gen = "./gen.py"
ans = "./brute.py"
sol = "./sol.o"

for round in itertools.count(1):
    if round % 100 == 0:
        print(f"{round = }")

    gen_data = subprocess.run(
        [gen],
        capture_output=True,
        text=True,
        check=True,
    )

    # print(f"{gen_data.stdout = }")

    ans_data = subprocess.run(
        [ans],
        input=gen_data.stdout,
        capture_output=True,
        text=True,
    )

    if ans_data.returncode != 0:
        print(f"{' ans crashed ':-^72}")
        print(f"{f' after {round} rounds':-^72}")
        print(f"{' gen ':-^72}")
        print(gen_data.stdout)

        break

    sol_data = subprocess.run(
        [sol],
        input=gen_data.stdout,
        capture_output=True,
        text=True,
    )

    if sol_data.returncode != 0:
        print(f"{' Sol crashed ':-^72}")
        print(f"{f' after {round} rounds':-^72}")
        print(f"{' gen ':-^72}")
        print(gen_data.stdout)
        print(f"{' ans ':-^72}")
        print(ans_data.stdout)

        break

    ans_vals = [int(i) for i in ans_data.stdout.split()]
    sol_vals = [int(i) for i in sol_data.stdout.split()]

    # print(f"{ans_vals}")
    # print(f"{sol_vals}")

    if ans_vals != sol_vals:
        print(f"{' Found diffrence ':-^72}")
        print(f"{f' After {round} rounds':-^72}")
        print(f"{' Gen ':-^72}")
        print(gen_data.stdout)

        print(f"{' Ans ':-^72}")
        print(ans_data.stdout)

        print(f"{' Sol ':-^72}")
        print(sol_data.stdout)

        break
