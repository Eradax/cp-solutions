#!/usr/bin/env python3

n, t = map(int, input().split())
v = [int(i) for i in input().split()]

match t:
    case 1:
        print(7)
    case 2:
        print(["Equal", "Bigger", "Smaller"][(v[0] > v[1]) + 2 * (v[1] > v[0])])
    case 3:
        print(sorted(v[:3])[1])
    case 4:
        print(sum(v))
    case 5:
        print(sum(filter(lambda x: x % 2 == 0, v)))
    case 6:
        print(''.join(map(lambda x: chr(ord('a') + x % 26), v)))
    case 7:
        vis = [0] * n
        i = 0
        while True:
            if i < 0 or i >= n:
                print("Out")
                break

            if i == n - 1:
                print("Done")
                break

            if vis[i]:
                print("Cyclic")
                break

            vis[i] = 1
            i = v[i]
