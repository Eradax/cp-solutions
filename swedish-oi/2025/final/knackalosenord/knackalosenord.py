#!/usr/bin/env python3
import string
from sys import stderr


def dbg(*s):
    print(f"{' DBG Start ':-^72}", file=stderr)
    for i in s:
        print(f"{i}", file=stderr)

    print(f"{' DBG End ':-^72}", file=stderr)


def query(p):
    print(f"? {p}")
    ans = int(input())
    return ans


def answer(p):
    print(f"! {p}")


n, k = map(int, input().split())

chars = string.ascii_lowercase[:k]

amount = [0] * k
for i in range(k - 1):
    amount[i] = query(chars[i] * n)
amount[k - 1] = n - sum(amount)

dbg(amount)

count = [0] * k
cp = 0

passwd = chars[cp] * amount[cp]
count[cp] = amount[cp]


while len(passwd) < n:
    if count[cp] == amount[cp]:
        cp += 1
        continue

    lo = 0
    hi = len(passwd)
    add = chars[cp] * (amount[cp] - count[cp])

    dbg(cp, lo, hi, add)

    while lo < hi:
        mi = lo + (hi - lo) // 2

        newpass = passwd[:mi] + add

        ans = query(newpass)

        if ans != len(newpass):
            hi = mi
        else:
            lo = mi + 1

    newpass = passwd[:lo] + add
    if query(newpass) != len(newpass):
        lo -= 1

    dbg(lo)

    passwd = passwd[:lo] + chars[cp] + passwd[lo:]

    count[cp] += 1

answer(passwd)
