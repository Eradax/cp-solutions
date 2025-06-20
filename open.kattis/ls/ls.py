def ma(pa, s):
    i, j = 0, 0
    st = -1
    b = 0
    while i < len(s):
        if j < len(pa) and (pa[j] == s[i]):
            i += 1
            j += 1
        elif j < len(pa) and pa[j] == '*':
            st = j
            b = i
            j += 1
        elif st != -1:
            j = st + 1
            b += 1
            i = b
        else:
            return 0

    while j < len(pa) and pa[j] == '*':
        j += 1

    return j == len(pa)


p = input()
n = int(input())
for _ in range(n):
    name = input()
    if ma(p, name):
        print(name)
