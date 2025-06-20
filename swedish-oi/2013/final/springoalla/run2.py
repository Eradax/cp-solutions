#!/usr/bin/env python3
import itertools
import sys  # Import sys
from subprocess import run, PIPE  # Import PIPE

gen = "./gen.py"
ans = "./ans.o"
sol = "./sol.o"
validator = "./validator.py"  # Path to the validator script

for i in itertools.count(1):
    if i % 100 == 0:
        print(f"{i = }")

    gend = run(
        [gen],
        capture_output=True,
        check=True,
    )
    input_data = gend.stdout  # Store input data

    ansd = run([ans], input=input_data, capture_output=True)

    if ansd.returncode != 0:
        print("ANS crashed")
        print(input_data.decode())
        break

    sold = run([sol], input=input_data, capture_output=True)

    if sold.returncode != 0:
        print("SOL crashed")
        print(input_data.decode())
        break

    solution_output_data = sold.stdout  # Store solution output

    # --- Run Validator ---
    # Pipe input data THEN solution output data to the validator
    validator_input = input_data + solution_output_data
    vald = run(
        [
            sys.executable,
            validator,
        ],  # Use sys.executable to ensure correct python version
        input=validator_input,
        capture_output=True,  # Capture stderr for error messages
    )

    if vald.returncode != 0:
        print("*" * 20 + " VALIDATOR FAILED " + "*" * 20)
        print("Input:")
        print(input_data.decode())
        print("-" * 20)
        print("SOL Output:")
        print(solution_output_data.decode())
        print("-" * 20)
        print("Validator Error Message:")
        print(vald.stderr.decode())  # Print validator's stderr
        print("*" * 58)
        # Decide if you want to break or continue testing
        # break # Usually break on first validation failure
        # If the validator exits with 1, it might be an internal error,
        # otherwise (e.g., 42) it's a WA from the solution.
        if vald.returncode == 42:
            print("(Validator indicated Wrong Answer from solution)")
        else:
            print(f"(Validator exited with code {vald.returncode})")
        break  # Stop testing

    # --- Compare ANS and SOL (if validator passed) ---
    try:
        ans_vals = [int(x) for x in ansd.stdout.decode().split()]
        sol_vals = [
            int(x) for x in solution_output_data.decode().split()
        ]  # Use stored output
    except ValueError:
        print(
            "Error parsing integer values from ANS or SOL output after validation passed."
        )
        print("Input:\n", input_data.decode())
        print("ANS Output:\n", ansd.stdout.decode())
        print("SOL Output:\n", solution_output_data.decode())
        break

    # Check primary objective (ts)
    if not ans_vals or not sol_vals:
        print("Error: Empty output from ANS or SOL.")
        print("Input:\n", input_data.decode())
        print("ANS Output:\n", ansd.stdout.decode())
        print("SOL Output:\n", solution_output_data.decode())
        break

    if ans_vals[0] != sol_vals[0]:
        print(f"Found TS diff after {i} iterations (Validator Passed)")
        print("Input:")
        print(input_data.decode())
        print("--------------------")
        print("ANS Output (Expected TS):")
        print(ansd.stdout.decode())
        print("--------------------")
        print("SOL Output (Actual TS):")
        print(solution_output_data.decode())
        break

    # Check secondary objective (ns) - IMPORTANT based on problem statement
    if len(ans_vals) > 1 and len(sol_vals) > 1:
        if ans_vals[1] != sol_vals[1]:
            print(f"Found NS diff after {i} iterations (TS Matched, Validator Passed)")
            print("Input:")
            print(input_data.decode())
            print("--------------------")
            print("ANS Output (Expected NS):")
            print(ansd.stdout.decode())
            print("--------------------")
            print("SOL Output (Actual NS):")
            print(solution_output_data.decode())
            break
    elif len(ans_vals) < 2 or len(sol_vals) < 2:
        print(
            f"Warning after {i} iterations: ANS or SOL output missing NS value, cannot compare."
        )
        # Decide if this is an error or acceptable
