from math import floor

n = int(input())

for _ in range(n):
    num = float(input())

    cnt = round(num / 0.015)

    if (
        floor(100 * cnt * 0.015) / 100 == num
        or floor(100 * (cnt - 1) * 0.015) / 100 == num
        or floor(100 * (cnt + 1) * 0.015) / 100 == num
    ):
        print("VALID")
    else:
        print("IMPOSSIBLE")
