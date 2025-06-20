n, s = input().split()
n = int(n)
a = 0

vals = {
    'A': 11,
    'K': 4,
    'Q': 3,
    'J': 2,
    'T': 10,
    '9': 0,
    '8': 0,
    '7': 0,
}

for i in range(4 * n):
    p, q = input()

    a += vals[p] 
    if q == s:
        if p == 'J':
            a += 18
        if p == '9':
            a += 14

print(a)
