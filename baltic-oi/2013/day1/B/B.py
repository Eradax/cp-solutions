def isPalindrome(s):
    return any(c in s[i+1:i+3] for i, c in enumerate(s))

lo, hi = map(int, input().split())

ans = 0
for i in range(lo, hi+1):
    ans += 1 - isPalindrome(str(i))

print(ans)
# print(f"{ans = }")
