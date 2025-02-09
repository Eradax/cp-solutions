#!/usr/bin/env python3
import subprocess
import itertools

from gen import gen
from brute import solve as ans
from solve import solve as sol

for round in itertools.count(1):
    if round % 100 == 0:
        print(f"{round = }")

    gen_data = gen(3, 3)

    # print(f"{gen_data = }")

    ans_data = ans(*gen_data)
    sol_data = sol(*gen_data)
    # ans_data = sol_data

    if ans_data != sol_data:
        print(f"{' Found diffrence ':-^72}")
        print(f"{f' After {round} rounds':-^72}")
        print(f"{' Gen ':-^72}")
        print(gen_data)

        print(f"{' Ans ':-^72}")
        print(ans_data)

        print(f"{' Sol ':-^72}")
        print(sol_data)

        break
