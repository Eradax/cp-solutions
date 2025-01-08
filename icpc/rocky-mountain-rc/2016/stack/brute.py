#!/usr/bin/env python3


def solve(string, stack):
    if not string:
        return len(stack)

    if not stack:
        return 1 + solve(string[:-1], string[-1])

    if string[-1] == stack[-1]:
        return solve(string[:-1], stack)

    return min(
        1 + solve(string, stack + string[-1]),
        1 + solve(string, stack[:-1]),
    )


t = int(input())

for i in range(t):
    line = input()

    ans = solve(line, "") + len(line)

    print(ans)
