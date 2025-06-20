#!/usr/bin/env pypy3
gd, gb, gf, gt0, gt1, gt2 = map(int, input().split())


def solve(d, b, ft, et, tf):
    if d >= gd:
        return b

    ft = ft.copy()
    et = et.copy()

    f = ft[0] * 3 + tf
    e = et[0] * 3

    ft = ft[1:] + ft[:1]
    et = et[1:] + et[:1]

    ans = (-1, 0, 0, 0)

    for ff in range(f + 1):
        ft[2] += ff
        b += (f - ff) * 100

        for ee in range(e + 1):
            et[2] += ee
            b += (e - ee) * 500

            tmp = solve(d + 1, b, ft, et, 0)
            if tmp > ans[0]:
                ans = (tmp, ff, ee, 0)

            if b >= 400:
                et[2] += 1
                b -= 400

                tmp = solve(d + 1, b, ft, et, 0)
                if tmp > ans[0]:
                    ans = (tmp, ff, ee, 1)

                et[2] -= 1
                b += 400

                b += 100
                tmp = solve(d + 1, b, ft, et, 0)
                if tmp > ans[0]:
                    ans = (tmp, ff, ee, 2)
                b -= 100

            et[2] -= ee
            b -= (e - ee) * 500

        ft[2] -= ff
        b -= (f - ff) * 100

    # print(f"{d, b, ft, et = }")
    # print(f"{ans = }")

    return ans[0]


ans = solve(0, gb, [gt0, gt1, gt2], [0, 0, 0], gf)
print(ans)
