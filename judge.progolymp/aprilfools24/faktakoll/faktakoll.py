#!/usr/bin/env python3
import random
hardTruths = [
	("Sverige har vunnit IOI", "två gånger", True),
	("Joshua Andersson hade ", "692 contributions på Github år 2023", True),
	("Lösningen till Problemhunt är samma som ett av problemen på denna sida ", "https://open.kattis.com/problem-sources/Doris 2023 deltävling 2", True)		
]

hardLies = [
	("Harry Zhang hade ", "420 contributions på Github år 2023", False)
]

songs = [
	"Playing God",
	"G.O.A.T",
	"ABC",
	"O.D",
	"Goose",
	"Champagne"
]

q = input()

if '=' in q:
	print(eval(q.replace('=', '==')))
elif q.startswith("Bandet Polyphia"):
	print(any(i in q for i in songs))
elif any(q.startswith(i[0]) for i in hardTruths):
	print(any(q.endswith(i[1]) for i in hardTruths))
elif any(q.startswith(i[0]) for i in hardLies):
	print(not any(q.endswith(i[1]) for i in hardLies))
else:
	print(bool(random.randint(0,1)))

