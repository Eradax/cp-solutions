#!/usr/bin/env python3
import itertools
import subprocess

gen = "./gen.py"
ans = "./brute.py"
sol = "./run.sh"

for i in itertools.count(1):
    if i % 50 == 0:
        print(f"{i = }")

    gen_proc = subprocess.run(
        [gen],
        capture_output=True,
        text=True,
        check=True,
    )

    gen_data = gen_proc.stdout

    ans_proc = subprocess.run(
        [ans],
        capture_output=True,
        text=True,
        input=gen_data,
        check=True,
    )

    ans_data = ans_proc.stdout

    sol_proc = subprocess.run(
        [sol],
        capture_output=True,
        text=True,
        input=gen_data,
    )

    sol_data = sol_proc.stdout

    if sol_proc.returncode != 0:
        print("------- Found crash ---------")
        print("--------- Gen Data ----------")
        print(gen_data)

        exit()

    if sol_proc.stderr.strip():
        print("------- Found error ---------") 
        print("--------- Gen Data ----------")
        print(gen_data)
        print("--------- Error Data --------")
        print(sol_proc.stderr)

        exit()

    if [int(i) for i in ans_data.split()] != [
        int(i) for i in sol_data.split()
    ]:
        print("------- Found missmatch -----")
        print("-------- Gen Data -----------")
        print(gen_data)

        print("-------- Ans Data -----------")
        print(ans_data)

        print("-------- Sol Data -----------")
        print(sol_data)

        exit()
