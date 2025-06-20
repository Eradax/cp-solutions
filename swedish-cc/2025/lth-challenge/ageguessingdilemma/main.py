b = int(input())

div = 1 + b

lo = 0
hi = 10**9+1

def ask(i):
    print(i, flush=True)
    r = input()
    if r == "higher":
        return -1
    if r == "correct":
        return 0
    return 1

while lo +1 < hi:
    mi = lo + (hi - lo + div - 1) // div

    q = ask(mi)
    if q == 0:
        exit()
    if q == 1:
        hi = mi
    else:
        lo = mi


