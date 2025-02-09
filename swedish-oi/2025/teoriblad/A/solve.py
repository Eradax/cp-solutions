#!/usr/bin/env python3
from icecream import ic as dbg
# def dbg(*k): pass

MOD = 10**9 + 7


"""
split the original intervals into smaller intervals such that for each index
in the interval it will be covered bu the exact same segments
"""


def get_split_intervals(intervals):
    intervals = sorted(intervals)
    dbg(intervals)

    ret = [intervals[-1]]

    largest_right = -1
    for left, right in intervals[::-1]:
        dbg(left, right)
        if right >= largest_right:
            largest_right = right
        else:
            ret.append([left, right])

    dbg(ret)

    intervals = ret

    boundary_points = set()
    for l, r in intervals:
        boundary_points.add(l)
        boundary_points.add(r + 1)
    sorted_boundary_points = sorted(list(boundary_points))

    new_intervals = []
    for i in range(len(sorted_boundary_points) - 1):
        start = sorted_boundary_points[i]
        end = sorted_boundary_points[i + 1] - 1
        if start <= end:
            new_intervals.append((start, end))

    sorted_segments = sorted(intervals, key=lambda x: x[0])

    # Merge overlapping or adjacent segments
    merged = [sorted_segments[0]]
    for seg in sorted_segments[1:]:
        last = merged[-1]
        if seg[0] <= last[1]:
            # Merge the segments
            new_seg = (last[0], max(last[1], seg[1]))
            merged[-1] = new_seg
        else:
            merged.append(seg)

    # Prepare start and end arrays for binary search
    starts = [seg[0] for seg in merged]
    ends = [seg[1] for seg in merged]

    # Check each point using binary search
    import bisect

    result = []
    for p in new_intervals:
        idx = bisect.bisect_right(starts, p[0]) - 1
        if idx >= 0 and ends[idx] >= p[0]:
            result.append(p)

    result.sort()

    return result


def solve(n, intervals):
    intervals.sort(key=lambda x: x[1])

    new_intervals = get_split_intervals(intervals)
    new_n = len(new_intervals)

    new_intervals.sort(key=lambda x: x[1])

    dbg(n, intervals)
    dbg(new_n, new_intervals)

    assert new_n <= 2 * n - 1

    prend = [-1] * new_n
    intp = [0, 0]
    for nintp in range(new_n):
        dbg(intp, nintp)

        while (
            intp[0] + 1 < n
            and intervals[intp[0] + 1][1] < new_intervals[nintp][0]
        ):
            intp[0] += 1

        while intervals[intp[0]][1] != new_intervals[intp[1]][1]:
            dbg(intp)
            intp[1] += 1

        if intervals[intp[0]][1] < new_intervals[nintp][0]:
            prend[nintp] = intp[1]

    dbg(prend)

    intervals.sort()
    new_intervals.sort()

    dp_place = [-1] * (new_n + 1)  # solve up to i, not including
    dp_ways = [-1] * (new_n + 1)  # solve up to i, not including

    dp_place[0] = 0
    dp_ways[0] = 1

    for i in range(new_n):
        l, r = new_intervals[i]

        prev_endi = prend[i] + 1

        dbg(i, l, r, prev_endi)

        dp_place[i + 1] = 1 + dp_place[prev_endi]
        dp_ways[i + 1] = ((r - l + 1) * dp_ways[prev_endi]) % MOD

    dbg(dp_place)
    dbg(dp_ways)

    min_place = 1e18
    max_ways = 0

    for i in range(new_n)[::-1]:
        dbg(i, min_place, max_ways)

        if new_intervals[i][0] < intervals[-1][0]:
            break

        if dp_place[i + 1] > min_place:
            dbg("continue")
            continue

        if dp_place[i + 1] == min_place:
            dbg("equal")
            max_ways += dp_ways[i + 1]

            max_ways %= MOD

        if dp_place[i + 1] < min_place:
            dbg("less")
            min_place = dp_place[i + 1]
            max_ways = dp_ways[i + 1]

    return max_ways


if __name__ == "__main__":
    n = int(input())
    intervals = []
    for _ in range(n):
        l, r = map(int, input().split())
        intervals.append((l, r))
    print(solve(n, intervals))
