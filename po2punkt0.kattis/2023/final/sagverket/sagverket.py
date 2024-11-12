#!/usr/bin/env python3

from collections import Counter as C

def send_ans(guess: list[int]):
    print("!", *guess, flush=True)
    exit()

queries = []
def query(guess: int):
    print(f"? {guess}", flush=True)
    nums = C(map(int, input().split()))

    queries.append(nums)
    return nums

def apply_fix(count: C, idx: int):
    if not idx in count:
        count[idx] = 0
    else:
        count[idx] -= 1
    
    if not idx+1 in count:
        count[idx+1] = 0
    else:
        count[idx+1] += 1


def diff(c1: C, c2: C):
    diffs = [*(c1-c2)]

    if diffs:
        ret = diffs[0]

        # print(f"{diffs = }")
    else:
        ret = -1

    return ret

def main():
    global queries
    n, t = map(int, input().split())

    query(1)
    end = sum(queries[-1].elements()) + 1

    if n == 1:
        send_ans([end])

    vals = []


    if queries[-1][0] > 0:
        val = 1
        # print("Special case zero")
    else:
        query(2)
        val = diff(queries[-2], queries[-1]) + 1

        queries = queries[:-1]
        # print("Normal case non zero")

    vals.append(val)

    for i in range(n-2):
        query(vals[-1] + 1)

        # print(f"{i = }")
        # print(f"{vals = }")
        #
        # print(f"M1 = {queries[-2]}")
        # print(f"M2 = {queries[-1]}")

        if i:
            apply_fix(queries[-2], vals[i] - vals[i-1] - 1)
        else:
            if vals[0]-1 in queries[-2]:
                queries[-2][vals[0] - 1] -= 1
            else:
                queries[-2][vals[0] - 1]  = 0

            if 1 in queries[-2]:
                queries[-2][1] += 1
            else:
                queries[-2][1] = 0

        # print(f"M1 = {queries[-2]}")
        # print(f"M2 = {queries[-1]}")

        val = diff(queries[-2], queries[-1])

        vals.append(vals[-1] + val)

    vals.append(end)

    send_ans(vals)

if __name__ == "__main__":
    main()

