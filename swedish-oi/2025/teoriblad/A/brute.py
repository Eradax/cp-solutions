#!/usr/bin/env python3
import sys
import itertools

MOD = 10**9 + 7

def solve(n, intervals):
    positions = set()
    for l, r in intervals:
        positions.update(range(l, r + 1))
    positions = sorted(positions)
    m = len(positions)
    if m == 0:
        return 0
    
    min_pegs = None
    count = 0
    
    for k in range(1, m + 1):
        for subset in itertools.combinations(positions, k):
            valid = True
            for l, r in intervals:
                covered = False
                for x in subset:
                    if l <= x <= r:
                        covered = True
                        break
                if not covered:
                    valid = False
                    break
            if valid:
                if min_pegs is None:
                    min_pegs = k
                    count = 1
                elif k == min_pegs:
                    count += 1
        if min_pegs is not None:
            break
    
    return count % MOD if min_pegs is not None else 0


# def solve(n, intervals):
#     """
#     Solve this problem by doing the following dp
#
#     we sort all the intervals and divide them up into parts that are
#     exactly the same everywhere, there will be up to 2*n - 1.
#
#     Then the dp will do something similar to the following:
#     dp[i] = number of different ways and how many pinns are needed to
#     place such that the first i "sub intervals" are all covered.
#     """
#
#     sorted_indices = sorted(range(n), key=lambda i: intervals[i][1])
#     sorted_intervals = [intervals[i] for i in sorted_indices]
#     memo_dp = {}
#     memo_count = {}
#
#     def get_min_pins_and_ways(start_index):
#         if start_index == n:
#             return 0, 1
#         if start_index in memo_dp:
#             return memo_dp[start_index], memo_count[start_index]
#
#         current_interval_index = start_index
#         current_interval = sorted_intervals[current_interval_index]
#         l, r = current_interval
#         min_pins = float("inf")
#         ways = 0
#         optimal_locations = []
#
#         for location in range(l, r + 1):
#             next_unsecured_index = n
#             secured_indices_in_step = set()
#             for i in range(start_index, n):
#                 interval_l, interval_r = sorted_intervals[i]
#                 if interval_l <= location <= interval_r:
#                     secured_indices_in_step.add(i)
#
#             temp_next_unsecured_index = n
#             for i in range(start_index, n):
#                 if i not in secured_indices_in_step:
#                     temp_next_unsecured_index = i
#                     break
#             else:
#                 temp_next_unsecured_index = n
#
#             pins_needed_rest, ways_rest = get_min_pins_and_ways(
#                 temp_next_unsecured_index
#             )
#             total_pins = 1 + pins_needed_rest
#
#             if total_pins < min_pins:
#                 min_pins = total_pins
#                 ways = ways_rest
#                 optimal_locations = [location]
#             elif total_pins == min_pins:
#                 ways = (ways + ways_rest) % MOD
#                 optimal_locations.append(location)
#
#         memo_dp[start_index] = min_pins
#         memo_count[start_index] = ways
#         return min_pins, ways
#
#     min_pins, num_ways = get_min_pins_and_ways(0)
#     return num_ways


# def solve(n, intervals):
#     # Sort intervals by left endpoint (and then by right endpoint).
#     intervals.sort(key=lambda x: (x[0], x[1]))
#     # dp[i] = minimum number of pins needed to cover intervals i..n-1
#     # ways[i] = number of ways (mod MOD) to cover intervals i..n-1
#     # with dp[i] pins.
#     dp = [0] * (n + 1)
#     ways = [0] * (n + 1)
#     dp[n] = 0
#     ways[n] = 1  # no intervals -> one way
#
#     # Process intervals backwards: state i = cover intervals[i...n-1]
#     for i in range(n - 1, -1, -1):
#         best = float("inf")
#         best_count = 0
#         # Start with the intersection A(i,i) = [L, R] = [l_i, r_i]
#         L, R = intervals[i]
#         # current_size = size of A(i,k) = R-L+1 (if nonempty)
#         if L > R:
#             continue  # should not happen
#         current_size = R - L + 1
#
#         # Try all possible k (i <= k < n) such that A(i,k) is nonempty.
#         for k in range(i, n):
#             if k > i:
#                 # update the intersection with interval k
#                 L = max(L, intervals[k][0])
#                 R = min(R, intervals[k][1])
#                 if L > R:
#                     break  # intersection empty => cannot extend block further
#                 current_size = R - L + 1
#
#             # Compute size of A(i, k+1) if possible
#             if k < n - 1:
#                 newL = max(L, intervals[k + 1][0])
#                 newR = min(R, intervals[k + 1][1])
#                 if newL <= newR:
#                     next_size = newR - newL + 1
#                 else:
#                     next_size = 0
#             else:
#                 next_size = 0
#
#             # The valid x for which the block “ends” exactly at k are those in
#             # A(i,k) but not in A(i,k+1) (if that intersection exists).
#             if next_size > 0:
#                 c = current_size - next_size
#             else:
#                 c = current_size
#
#             # Candidate: use one pin (placed at one of these c positions)
#             # to cover intervals i..k, and then optimally cover intervals k+1..
#             candidate = 1 + dp[k + 1]
#             if candidate < best:
#                 best = candidate
#                 best_count = (c * ways[k + 1]) % MOD
#             elif candidate == best:
#                 best_count = (best_count + c * ways[k + 1]) % MOD
#         dp[i] = best
#         ways[i] = best_count
#
#     return ways[0] % MOD

def main_brute():
    n = int(input())
    intervals = []
    for _ in range(n):
        l, r = map(int, input().split())
        intervals.append((l, r))
    print(solve(n, intervals))

if __name__ == "__main__":
    main_brute()
