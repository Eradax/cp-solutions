names = set(open("./out.txt").read().split())
names2 = names

print(len(names))

letters = "qwertyuiopasdfghjklzxcvbnm"
vow = "aeiou"

for name in names:
    for i in range(4):
        for l in letters:
            nw = name[:i] + l + name[i + 1 :]
            if nw != name and nw in names2:
                print(name, nw)
                names2.remove(nw)

for word in names2:
    assert len(word) == 4
    assert sum(word.count(i) for i in vow) == 2
