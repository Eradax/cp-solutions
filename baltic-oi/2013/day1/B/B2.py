def isPalindrome(s):
    return any(c in s[i+1:i+3] for i, c in enumerate(s))

lo, hi = map(int, input().split())

def large(n):
    k = len(str(n))
    ans = 10
    for i in range(k-1):
        tmp = 81 * pow(8, i)
        ans += tmp
    return ans

def rarge(n, endin):
    if (n < 999): return small(n)
    n = str(n)
    k = len(n)

    ans = 0
    ans += (int(n[:2])) * pow(8, k-2)

    """
    n = 123456
    a = 120000
    """



def small(n):
    ans = 0
    for i in range(0, n+1):
        ans += 1 - isPalindrome(str(i))
    return ans;

def upto(k):
    word = k
    k = len(str(k))
    dps = [ [ [1] * 10 for _ in range(10)] for _ in range(20)]
    # dps[K][i][j] the number of palindrome-free strings of length `K+2` with the last two
    # characters being `i` and `j`
    for i in range(10):
        dps[0][i][i] = 0
    
    ans = 10 + sum(dps[0][i][j] for i in range(1, 10) for j in range(10))

    for K in range(k - 2):
        dps[K+1] = [[dps[K][i][j] for j in range(10)] for i in range(10)]

        for i in range(10):
            for j in range(10):
                dps[K+1][i][j] = sum(
                    0 if (i == m or i == j) else dps[K][j][m]
                    for m in range(10)
                )
        ans += sum(dps[K+1][i][j] for i in range(1, 10) for j in range(10))


    print("---------- DPS ----------\n")
    for dp in dps[:k-1]:
        print(f"---------- DP ----------")
        for row in dp:
            print(*row)
        print("---------- END DP ----------\n")
    print("---------- END DPS ----------")

    return ans

ll = (upto(lo) if lo > 999 else small(lo)) - 1 + isPalindrome(str(lo))
rr = (upto(hi) if hi > 999 else small(hi))

rr2 = (large(hi) if hi > 999 else small(hi))

print(f"{rr2 = }")
print(f"{ ll = }")
print(f"{rr = }")
print(rr - ll)
