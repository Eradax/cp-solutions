#!/usr/bin/env python3
#
# Testing tool for the task Quack.
#
# Usage:
#
#   python3 testing_tool.py [--silent] program... < input.txt
#
# input.txt uses the following format:
#
#   N Q T
#   x1 x2 x3 ... xN
#
# where N is the number of hidden ducks, Q is the maximum allowed "?"-queries, and T is which test group this testcase belongs to.
# x1 x2 x3 ... xN are the respective positions of the N ducks.
#
#
# For example, if you have a Python solution that you would run using
# "python3 file.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python3 file.py < input.txt
#
# where input.txt is a file that contains e.g.
#
# 2 3 0 
# 100 10000
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
        N, Q, T = map(int, input().split())
    except Exception:
        error("bad input format: failed to parse first line as three integers N, Q, and T")
    
    try:
        xs = [*map(int, input().split())]
        xs.sort()
    except:
        error("bad input format: could not read second line as a list of integers x1 x2 x3 ... xN")

    if N != len(xs):
        error(f"invalid amount of positions: {len(xs)=} != {N=}")
    for x in xs:
        if not (0 <= x <= 10**9):
            error(f"invalid position x: Position {x} is not within the interval [0,10^9]")
    
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    if not silent:
        print(f"[*] Running with {N=} {Q=}\n{xs=}")

    proc.stdin.write(f"{T}\n".encode("utf8"))
    proc.stdin.flush()
    print(f"< {T}")

    def findDuck(x: int, xs: list[int]) -> int:
        if x >= xs[-1]: return xs[-1]
        if x <= xs[0]: return xs[0]
        lo = 0; hi = len(xs)-1
        while lo < hi:
            mi = (lo + hi + 1)//2
            if xs[mi] <= x: lo = mi
            else: hi = mi - 1
        if abs(xs[lo+1] - x) >= abs(xs[lo] - x): return xs[lo]
        return xs[lo+1]

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
            if guesses > Q:
                error("Wrong answer: too many guesses")

            try:
                guess = int(guess)
            except Exception:
                error(f"bad input format: guess {guess} is not an integer")

            if not (-10**9 <= guess <= 2*10**9):
                error("Wrong answer: guess out of bound")
           

            pos = findDuck(guess, xs)
            proc.stdin.write(f"{pos}\n".encode("utf8"))
            proc.stdin.flush()
            if not silent:
                print(f"< {pos}")
        elif command == "!":
            try:
                guess = int(guess)
            except Exception:
                error(f"bad input format: guess {guess} is not an integer")

            line = proc.stdout.readline().decode("utf8")
            line = line.strip()
            
            try:
                guessed_pos = [*map(int,line.split())]
            except Exception:
                error(f"bad input format: guess {guessed_pos} could not be turned into a list of integers")

            if len(guessed_pos) != guess:
                error(f"Program answered guessed {guess} ducks, but only output {len(guessed_pos)} ducks")

            if guess != N:
                print(f"[*] Wrong answer: did not guess correct number of ducks. Guessed {guess}, correct is {N=}")
                exit(0)
            
            guessed_pos.sort()

            if guessed_pos == xs:
                print(f"[*] OK: found all ducks in {guesses} guesses")
                exit(0)
            else:
                print(f"[*] Wrong answer: did not find the correct positions of all ducks. Guessed {guessed_pos}, correct answer is {xs}")
                exit(0)
        else:
            error(f"Unknown command {command}")
        

if __name__ == "__main__":
    main()
