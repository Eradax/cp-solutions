#!/usr/bin/env python3
import subprocess
import itertools
import sys


def run_interactive():
    gen_proc = subprocess.run(["./gen.py"], capture_output=True, text=True, check=True)
    parts = gen_proc.stdout.strip().split()

    if len(parts) < 2:
        # print("Generator did not produce enough data")
        sys.exit(1)

    N = int(parts[0])
    Q = int(parts[1])

    if len(parts) != 2 + N:
        # print("Generator output does not match expected number of degrees")
        sys.exit(1)

    hidden_degrees = [0] * (N + 1)
    for i in range(N):
        hidden_degrees[i + 1] = int(parts[2 + i])

    proc = subprocess.Popen(
        ["./sol.o"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        text=True,
        bufsize=1,
    )

    proc.stdin.write(f"{N} {Q}\n")
    proc.stdin.flush()

    query_count = 0

    while True:
        line = proc.stdout.readline()
        if not line:
            break
        line = line.strip()
        if line.startswith("?"):
            parts = line.split()
            if len(parts) != 3:
                # print("Invalid query format:", line)
                proc.kill()
                sys.exit(1)
            try:
                i = int(parts[1])
                j = int(parts[2])
            except ValueError:
                # print("Invalid query numbers:", line)
                proc.kill()
                sys.exit(1)
            # Check that query indices are valid.
            if not (1 <= i <= N and 1 <= j <= N):
                # print("Query indices out of bounds:", line)
                proc.kill()
                sys.exit(1)
            query_count += 1
            if query_count > Q:
                # print("Exceeded query limit")
                proc.kill()
                sys.exit(1)
            # Compute the response: XOR of the degrees.
            response = hidden_degrees[i] ^ hidden_degrees[j]
            proc.stdin.write(f"{response}\n")
            proc.stdin.flush()
        # Handle final answer: must start with "!".
        elif line.startswith("!"):
            parts = line.split()
            if len(parts) != 1 + N:
                # print("Invalid answer format:", line)
                proc.kill()
                sys.exit(1)
            try:
                contestant_degrees = [int(x) for x in parts[1:]]
            except ValueError:
                # print("Invalid answer numbers:", line)
                proc.kill()
                sys.exit(1)
            # Since the order doesn't matter, we compare sorted lists.
            if sorted(contestant_degrees) == sorted(hidden_degrees[1:]):
                # print("Accepted!")
                ...
            else:
                print("Wrong answer!")
                print("Hidden degrees:", hidden_degrees[1:])
                print("Contestant answer:", contestant_degrees)
                exit(1)
            break
        else:
            # If any unexpected output is encountered, print it.
            print("Unexpected output from solution:", line)
            exit(1)

    proc.wait()


if __name__ == "__main__":
    for i in itertools.count(1):
        if (i % 100 == 0):
            print(f"{i = }")

        try:
            run_interactive()
        except:
            break
