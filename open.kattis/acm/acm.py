#!/usr/bin/env python3

def main():
	inp = input()

	solved = [0]*26
	rolling = [0]*26
	s = 0
	ans = 0
	while inp != '-1':
		time, problemID, judgement = inp.split()

		if not solved[ord(problemID) - ord('A')]:
			if judgement == "wrong":
				rolling[ord(problemID) - ord('A')] += 20
			else:
				solved[ord(problemID) - ord('A')] = 1
				s += 1
				ans += int(time) + rolling[ord(problemID) - ord('A')]
		inp = input()

	print(s, ans)

main()