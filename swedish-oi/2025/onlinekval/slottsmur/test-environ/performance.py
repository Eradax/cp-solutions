#!/usr/bin/env python3
import subprocess
import resource
import sys
from tqdm import tqdm


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default


gen = "./gen.py"
sol = "./sol"


def query(per: int):
    TIMES = 30

    tot = 0
    maxt = 0

    for i in tqdm(range(1, TIMES + 1)):
        gen_proc = subprocess.run(
            [gen, f"per={per}"],
            capture_output=True,
            text=True,
            check=True,
        )

        gen_data = gen_proc.stdout

        before = sum(resource.getrusage(resource.RUSAGE_SELF)[:2])

        sol_proc = subprocess.run(
            [sol],
            capture_output=True,
            text=True,
            input=gen_data,
        )

        after = sum(resource.getrusage(resource.RUSAGE_SELF)[:2])

        tot += after - before
        maxt = max(maxt, after - before)

    avg = tot / TIMES

    return avg, maxt


# lo = 0
# hi = 100
# while lo <= hi:
#     lo_third = lo + (hi - lo) // 3
#     hi_third = (
#         lo
#         + (hi - lo) // 3
#         + (1 if 0 < hi - lo < 3 else (hi - lo) // 3)
#     )
#
#     if query(lo_third)[0] < query(hi_third)[0]:
#         lo = lo_third + 1
#     else:
#         hi = hi_third - 1
#
# print(f"{lo = }")
# print(f"{query(lo) = }")

print(f"{query(90) = }")
