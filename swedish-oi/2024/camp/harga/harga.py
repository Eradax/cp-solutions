#!/usr/bin/env python3
def t1(vals, m, func):
    seen = {vals[0]}
    t = 1
    val = vals[0]
    while len(seen) < m:
        t+=1
        val = func[val]

        if val in seen:
            t=-1
            break

        seen.add(val)
    print(t)


def t2(vals, m, n):
    from collections import defaultdict

    if len(set(vals)) < m:
        print(-1)
        return

    seen = defaultdict(lambda: 0)
    seen[vals[0]] += 1
    groups = 1
    idx = 0

    times = [-1]*n
    person = 0
    while person < n:
        while groups < m:
            idx = (idx+1)%n
            seen[vals[idx]] += 1
            if seen[vals[idx]] == 1:
                groups += 1

        seen[vals[person]] -= 1
        if seen[vals[person]] == 0:
            groups -= 1

        if idx >= person:
            times[person] = idx+1-person
        else:
            times[person] = n-person+idx+1

        person += 1

    print(*times)

def main():
    n, m = map(int, input().split())

    vals = [*map(int, input().split())]

    func = dict(zip(range(1, m+1), map(int, input().split())))

    if n==1:
        t1(vals, m, func)
    else:
        t2(vals, m, n)
main()

