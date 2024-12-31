#!/usr/bin/env python3
# https://vjudge.net/contest/651973#problem/A


import itertools

n, m = map(int, input().split())

line = input()

k = line.count("k")
r = line.count("r")
o = line.count("o")
d = line.count("d")

score = 0
score += k * k
score += r * r
score += o * o
score += d * d

mi = min(k // 2, r, o // 2, d)
# print(f"{mi = }")

score += 7 * mi

kk = k - 2 * mi
rr = r - mi
oo = o - 2 * mi
dd = d - mi

# print(f"{kk = }\n{rr = }\n{oo = }\n{dd = }")

best = score
# print(f"{best = }")
for i in itertools.combinations_with_replacement("krod", m):
    # print(f"{i = }")
    tmp = score
    kn = i.count("k")
    rn = i.count("r")
    on = i.count("o")
    dn = i.count("d")
    tmp += 2 * k * kn + kn * kn
    tmp += 2 * r * rn + rn * rn
    tmp += 2 * o * on + on * on
    tmp += 2 * d * dn + dn * dn

    tmp += 7 * min((kk + kn) // 2, rr + rn, (oo + on) // 2, dd + dn)
    best = max(best, tmp)
    # print(f"{best = }")

print(best)

