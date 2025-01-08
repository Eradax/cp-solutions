#!/usr/bin/env python3
import subprocess
import itertools
import io

gen = "./gen.py"
ans = "./brute.py"
sol = "./stack"

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

    same = ans_vals[0] == sol_vals[0]

    f = io.StringIO(gen_data.stdout)
    n, c = map(int, f.readline().split())
    d, s = zip(*(map(int, f.readline().split()) for _ in range(n)))

    size = 0
    seen = set()
    for i in sol_vals[1:]:
        i -= 1
        same = same and (size + max(d[i], s[i]) <= c and i not in seen)
        size += s[i]
        seen.add(i)

    if not same:
        print(f"{' Found diffrence ':-^72}")
        print(f"{f' After {round} rounds':-^72}")
        print(f"{' Gen ':-^72}")
        print(gen_data.stdout)

        print(f"{' Ans ':-^72}")
        print(ans_data.stdout)

        print(f"{' Sol ':-^72}")
        print(sol_data.stdout)

        break
