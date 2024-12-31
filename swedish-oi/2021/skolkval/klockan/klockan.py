#!/usr/bin/env python3
def main():
    energy = int(input())

    l, r = 0, 0

    prefixSum = [0] * 100000

    for h in range(24):
        for m in range(60):
            for s in range(60):
                # print(f"h:m:s: {h}:{m}:{s}")
                # print(f"Cost: {numToCost}")
                prefixSum[1 + (s + 60 * m + 3600 * h)] = prefixSum[
                    (s + 60 * m + 3600 * h)
                ] + numToCost([h, m, s])

    print(countPairsWithDiffK(prefixSum, 86401, energy))


costs = {0: 6, 1: 2, 2: 5, 3: 5, 4: 4, 5: 5, 6: 6, 7: 3, 8: 7, 9: 6}


def numToCost(arr):
    cost = 0
    digits = [int(i) for j in arr for i in list(f"{j:02}")]
    for digit in digits:
        cost += costs[digit]
    return cost


def binarySearch(arr, low, high, x):
    if high >= low:
        mid = low + (high - low) // 2
        if x == arr[mid]:
            return mid
        elif x > arr[mid]:
            return binarySearch(arr, (mid + 1), high, x)
        else:
            return binarySearch(arr, low, (mid - 1), x)

    return -1


def countPairsWithDiffK(arr, n, k):
    count = 0
    i = 0
    while i < n:
        while i - 1 >= 0 and arr[i] == arr[i - 1]:
            i += 1
        if binarySearch(arr, i + 1, n - 1, arr[i] + k) != -1:
            count += 1
        i += 1

    return count


main()
