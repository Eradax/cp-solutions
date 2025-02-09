#!/usr/bin/env python3
import time
import itertools

from gen import gen
from brute import solve as ans
from solve_tree import solve as sol, get_input


def valid(matching):
    match_len = len(matching)
    flag = True
    for (u, v), (w, x) in matching:
        if len({u, v, w, x}) == 4:
            flag = False
            break
    return flag


for round in itertools.count(1):
    if round % 1 == 0:
        print(f"{round = }")

    (n, m), edges = gen(16, 16, True)

    ans_len, ans_vals = ans(*get_input(*(n, m), edges, term=False))
    sol_len, sol_vals = sol(*get_input(*(n, m), edges, term=False))
    # ans_len, ans_vals = sol_len, sol_vals

    if (
        0
        or ans_len != sol_len
        or not valid(ans_vals)
        or not valid(sol_vals)
        or ans_len != m // 2
    ):
        print(f"{' Found diffrence ':-^72}")
        print(f"{f' After {round} rounds':-^72}")
        print(f"{' Gen ':-^72}")
        print((n, m), edges)

        print(f"{' Ans ':-^72}")
        print(ans_vals)

        print(f"{' Sol ':-^72}")
        print(sol_vals)

        break
