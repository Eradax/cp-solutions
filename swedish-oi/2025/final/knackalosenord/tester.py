#!/usr/bin/env python3
#
# Testing tool for the task Crack the Password.
#
# Usage:
#
#   python3 testing_tool.py [--silent] program... <input.txt
#
# input.txt uses the following format:
#
#   N K
#   P
#
# where N is the length of the password, whose characters consistent of the first K lowercase letters
# P is the hidden password 
#
#
# For example, if you have a Python solution that you would run using
# "python3 file.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python3 file.py < input.txt
#
# where input.txt is a file that contains e.g.
#
# 6 3
# bbacba
#
# If --silent is passed, the communication output will not be printed.
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
# Notably, this is not the program used to test your solution in Kattis
# 

import subprocess
import sys

def error(msg):
    print("ERROR:", msg)
    sys.exit(1)

def main():
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if not args or args == ["--help"] or args == ["-h"]:
        print("Usage:", sys.argv[0], "[--silent] program... <input.txt")
        sys.exit(0)
    
    try:
        N, K = map(int, input().split())
    except Exception:
        error("bad input format: failed to parse first line as two integers N and K")
    
    try:
        P = input()
    except:
        error("bad input format: could not read second line as P")

    if N != len(P):
        error(f"invalid P: {len(P)=} != {N=}")
    for c in P:
        if not (c >= 'a' and c <= chr(ord('a') + K - 1)):
            error(f"invalid P: character {c} is not among the {K=} first of the lowercase letters")
    
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    if not silent:
        print(f"[*] Running with {N=} {K=} {P=}")

    proc.stdin.write(f"{N} {K}\n".encode("utf8"))
    proc.stdin.flush()
    print(f"< {N} {K}")

    def longest_common_subsequence(s1: str, s2: str) -> int:
        prev = [0] * (len(s1) + 1)
        curr = [0] * (len(s1) + 1)

        for j in range(1, len(s2) + 1):
            for i in range(1, len(s1) + 1):
                if s1[i - 1] == s2[j - 1]:
                    curr[i] = prev[i - 1] + 1
                else:
                    curr[i] = max(prev[i], curr[i - 1])
            prev, curr = curr, prev

        return prev[-1]

    guesses = 0

    while True:
        line = proc.stdout.readline().decode("utf8")
        line = line.strip()
        if len(line.split()) != 2:
            error(f"Program sent guess with wrong format: {line}")
        command = line.split()[0]
        guess = line.split()[1]

        if not silent:
            print(f"> {command} {guess}")

        if command == "?":
            guesses += 1
            if guesses > 10000:
                error("Wrong answer: too many guesses")
            if len(guess) > N:
                error("Wrong answer: too long guess")
            for c in guess:
                if not (c >= 'a' and c <= chr(ord('a') + K - 1)):
                    error(f"wrong answer: invalid guess. character {c} is not among the {K=} first of the lowercase letters")

            lcs = longest_common_subsequence(guess, P)
            proc.stdin.write(f"{lcs}\n".encode("utf8"))
            proc.stdin.flush()
            if not silent:
                print(f"< {lcs}")
        elif command == "!":
            if guess == P:
                print(f"[*] OK: found password in {guesses} guesses")
                exit(0)
            else:
                print(f"[*] Wrong answer: found wrong password. Guessed {guess}, right is {P}")
                exit(0)
        else:
            error(f"Unknown command {command}")
        

if __name__ == "__main__":
    main()
