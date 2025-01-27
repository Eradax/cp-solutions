#!/usr/bin/env python3
import sys

n, k = map(int, input().split())

chars = "abcdefghijklmnopqrstuvwxyz"[:k]

passwd = ""


def query(p):
    # print(f"{p = }", file=sys.stderr)
    print(f"? {p}")
    ans = int(input())
    return ans


def answer(p):
    print(f"! {p}")


# a = query("a" * n)
# b = query("b" * n)
# c = n - a - b

amount = [0] * k
for i in range(k - 1):
    amount[i] = query(chars[i] * n)
amount[k - 1] = n - sum(amount)

# print(f"{a = }", file=sys.stderr)
# print(f"{b = }", file=sys.stderr)

# exit()

passwd = "a" * amount[0]

# print(f"1 {passwd = }", file=sys.stderr)

# exit()

# assert query(passwd) == len(passwd)

count = [0] * k

count[0] = amount[0]

for idx, char in enumerate(chars):
    ip = 0
    while len(passwd) < n and ip <= n and count[idx] < amount[idx]:
        if query(passwd[:ip] + char + passwd[ip:]) > len(passwd):
            passwd = passwd[:ip] + char + passwd[ip:]
            count[idx] += 1

            # print(f"2 {passwd = }", file=sys.stderr)
        ip += 1

        # print(f"3 {passwd = }", file=sys.stderr)


# ip = 0
# while len(passwd) < n and ip <= n:
#     if query(passwd[:ip] + "c" + passwd[ip:]) > len(passwd):
#         passwd = passwd[:ip] + "c" + passwd[ip:]
#
#         # print(f"2 {passwd = }", file=sys.stderr)
#     ip += 1
#
#     # print(f"3 {passwd = }", file=sys.stderr)

answer(passwd)
