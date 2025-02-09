#!/usr/bin/env python3


def solve(n, arr):
    cnt = [[0] * n for _ in range(3)]

    indexes = [[[] for _ in range(n)] for _ in range(3)]

    for i, row in enumerate(arr):
        for j, e in enumerate(row):
            e -= 1
            cnt[i][e] += 1
            indexes[i][e].append(j)

    # print(f"{cnt = }")
    # print(f"{indexes = }")

    exam = set()

    for i in range(n):
        col = [cnt[j][i] for j in range(3)]

        # print(f"{i = }")
        # print(f"{col = }")

        if any(map(lambda x: x == 0, col)) and any(col):
            for k in range(3):
                for kk in indexes[k][i]:
                    exam.add(kk)

    # print(f"{exam = }")

    done = set()

    while len(exam) > 0:
        # print(f"{exam = }")

        coli = exam.pop()
        done.add(coli)

        # print(f"{coli = }")

        for i in range(3):
            numi = arr[i][coli] - 1
            cnt[i][numi] -= 1

            if cnt[i][numi] == 0:
                for ii in range(3):
                    for col in indexes[ii][numi]:
                        if col not in done:
                            exam.add(col)

    # print(f"{cnt = }")

    res = [[] for _ in range(3)]
    for i in range(3):
        for j, r in enumerate(cnt[i]):
            # print(f"{r = }")

            if r > 0:
                res[i].append(j + 1)

    return n - len(res[0])


if __name__ == "__main__":
    n = int(input())
    arr = [[int(i) for i in input().split()] for _ in range(3)]

    res = solve(n, arr)

    print(res)
