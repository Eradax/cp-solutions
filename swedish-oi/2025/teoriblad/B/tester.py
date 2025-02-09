#!/usr/bin/env python3
import time
import itertools

from gen import gen
from brute import solve as ans
from solve import solve as sol


def valid(arr):
    match_len = len(arr)
    
    return all(sorted(arr[0]) == sorted(arr[i]) for i in range(3))


for round in itertools.count(1):
    if round % 1 == 0:
        print(f"{round = }")

    n, arr = gen(10000000)

    print("sol time")

    # ans_len = ans(n, arr)
    sol_len = sol(n, arr)
    ans_len = sol_len

    if (
        0
        or ans_len != sol_len
    ):
        print(f"{' Found diffrence ':-^72}")
        print(f"{f' After {round} rounds':-^72}")
        print(f"{' Gen ':-^72}")
        print(n, arr)

        print(f"{' Ans ':-^72}")
        print(ans_len)

        print(f"{' Sol ':-^72}")
        print(sol_len)

        break
