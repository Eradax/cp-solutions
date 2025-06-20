import itertools

vow = "aeiou"
con = "bcdfghjklmnpqrstvwxyz"

letters = vow + con

words = set()

for v in itertools.product(vow, repeat=2):
    v = list(v)
    for c in itertools.product(con, repeat=2):
        c = list(c)
        for i, j in itertools.combinations(range(4), 2):
            vc = v.copy()
            cc = c.copy()
            word = ""
            for k in range(4):
                if k in (i, j):
                    word += vc.pop()
                else:
                    word += cc.pop()
            words.add(word)

print(len(words))

used = set()

while words:
    top = words.pop()
    used.add(top)

    for i in range(4):
        for l in letters:
            nw = top[:i] + l + top[i + 1 :]
            if nw in words:
                words.remove(nw)

print(len(words))
print(len(used))

for word in used:
    assert len(word) == 4
    assert sum(word.count(i) for i in vow) == 2


# print(used)
