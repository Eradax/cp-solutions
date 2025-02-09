#!/usr/bin/env python3
import itertools


def solve(n, matrix):
    """
    Given a 3 x N matrix (as a list of 3 lists, each of length N),
    find the minimum number of columns to delete so that after deleting
    the chosen columns and sorting each row, all three rows become equal.
    This brute‐force solution tries all subsets of columns.
    """

    best_kept = 0

    for kept_size in range(n, 0, -1):
        for cols in itertools.combinations(range(n), kept_size):
            row1 = sorted(matrix[0][i] for i in cols)
            row2 = sorted(matrix[1][i] for i in cols)
            row3 = sorted(matrix[2][i] for i in cols)

            if row1 == row2 == row3:
                best_kept = kept_size
                break
        if best_kept:
            break

    min_deletions = n - best_kept

    return min_deletions


if __name__ == "__main__":
    n = int(input())
    arr = [[int(i) for i in input().split()] for _ in range(3)]

    res = solve(n, arr)

    print(res)
