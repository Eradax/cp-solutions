#!/usr/bin/env python3
import string

mayan = "𝋠𝋡𝋢𝋣𝋤𝋥𝋦𝋧𝋨𝋩𝋪𝋫𝋬𝋭𝋮𝋯𝋰𝋱𝋲𝋳"

eq = [
    ["tragedy", "time", "comedy"],
    ["repetition", "repetition", "learning"],
    ["fire", "water", "steam"],
    ["red", "blue", "purple"],
    ["icelander", "deadline", "procrastination"],
    ["throat", "potato", "danish"],
    ["kattis", "program", "verdict"],
    ["problem", "solution", "AC"],
    ["contest", "geometry", "WA"],
    ["nonsense", "annoyance", "this problem"],
]

elems = [
    "H",
    "He",
    "Li",
    "Be",
    "B",
    "C",
    "N",
    "O",
    "F",
    "Ne",
    "Na",
    "Mg",
    "Al",
    "Si",
    "P",
    "S",
    "Cl",
    "Ar",
    "K",
    "Ca",
    "Sc",
    "Ti",
    "V",
    "Cr",
    "Mn",
    "Fe",
    "Co",
    "Ni",
    "Cu",
    "Zn",
    "Ga",
    "Ge",
    "As",
    "Se",
    "Br",
    "Kr",
    "Rb",
    "Sr",
    "Y",
    "Zr",
    "Nb",
    "Mo",
    "Tc",
    "Ru",
    "Rh",
    "Pd",
    "Ag",
    "Cd",
    "In",
    "Sn",
    "Sb",
    "Te",
    "I",
    "Xe",
    "Cs",
    "Ba",
    "La",
    "Ce",
    "Pr",
    "Nd",
    "Pm",
    "Sm",
    "Eu",
    "Gd",
    "Tb",
    "Dy",
    "Ho",
    "Er",
    "Tm",
    "Yb",
    "Lu",
    "Hf",
    "Ta",
    "W",
    "Re",
    "Os",
    "Ir",
    "Pt",
    "Au",
    "Hg",
    "Tl",
    "Pb",
    "Bi",
    "Po",
    "At",
    "Rn",
    "Fr",
    "Ra",
    "Ac",
    "Th",
    "Pa",
    "U",
    "Np",
    "Pu",
    "Am",
    "Cm",
    "Bk",
    "Cf",
    "Es",
    "Fm",
    "Md",
    "No",
    "Lr",
    "Rf",
    "Db",
    "Sg",
    "Bh",
    "Hs",
    "Mt",
    "Ds",
    "Rg",
    "Cn",
    "Nh",
    "Fl",
    "Mc",
    "Lv",
    "Ts",
    "Og",
]

line = input()

if line.count("+") == 1:
    a, b = [i.strip() for i in line.split("+")]

    if a.isdigit() and b.isdigit():
        print(int(a) + int(b))
        exit()

    if a[0] == a[-1] == b[0] == b[-1] == '"':
        print(a[1:-1] + b[1:-1])
        exit()

    if a[:2] == b[:2] == "0x" and all(i in string.hexdigits for i in a[2:] + b[2:]):
        print(f"0x{int(a, 16) + int(b, 16):x}")
        exit()

    if all(i[:4] == "log(" and i[4:-1].isdigit() for i in (a, b)):
        print(f"log({int(a[4:-1]) * int(b[4:-1])})")
        exit()

    if a[0] == b[0] == "{" and a[-1] == b[-1] == "}":
        print(
            f"{{{', '.join(map(str, sorted(set(int(i) for i in (a[1:-1] + ', ' + b[1:-1]).split(', ') if i))))}}}"
        )
        exit()

    if a in elems and b in elems:
        print(elems[elems.index(a) + elems.index(b) + 1])
        exit()

    if all(i in mayan for i in a + b):
        n = sum(20 ** (len(a) - i - 1) * mayan.index(a[i]) for i in range(len(a)))
        n += sum(20 ** (len(b) - i - 1) * mayan.index(b[i]) for i in range(len(b)))
        num = ""
        if n == 0:
            num += mayan[n]
        while n:
            num += mayan[n % 20]
            n //= 20
        print(num[::-1])
        exit()

    if all(i.isdigit() for i in a.split(" mod ")) and all(
        i.isdigit() for i in b.split(" mod ")
    ):
        x, y = (int(i) for i in a.split(" mod "))
        z, w = (int(i) for i in b.split(" mod "))

        q = y * w
        p = (x + y * pow(y, -1, w) * (z - x)) % q

        print(f"{p} mod {q}")
        exit()

    if any(i[0] == a and i[1] == b for i in eq):
        for i in eq:
            if i[0] == a and i[1] == b:
                print(i[2])
        exit()

    print("fuck")
    exit()

if line.count("+") == 3:
    a, b, c, d = [i.strip() for i in line.split("+")]

    if all(i.isdigit() for i in (a, c)) and all(i[:-1].isdigit() for i in (b, d)):
        print(f"{int(a) + int(c)} + {int(b[:-1]) + int(d[:-1])}i")
        exit()

print("Fuck")
