s = input()
d = input()
lcs = input()

i = j = k = 0
out = []

while i < len(s) or j < len(d):
    if i >= len(s):
        out += [d[j]]
        j += 1
        continue

    if j >= len(d):
        out += [s[i]]
        i += 1
        continue

    if k >= len(lcs):
        out += [s[i]]
        i += 1
        continue

    if lcs[k] == s[i] == d[j]:
        out += [lcs[k]]
        k += 1
        i += 1
        j += 1
        continue

    if lcs[k] == s[i]:
        out += [d[j]]
        j += 1
        continue

    out += [s[i]]
    i += 1

print("".join(out))
