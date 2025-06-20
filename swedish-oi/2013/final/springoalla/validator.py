#!/usr/bin/env python3
import sys

# --- Helper Functions ---
def read_line():
    """Reads a line from stdin."""
    try:
        return sys.stdin.readline()
    except EOFError:
        sys.stderr.write("Validator Error: Unexpected EOF while reading input/output.\n")
        sys.exit(1) # Use 1 for internal validator errors

def read_ints():
    """Reads a line, splits by space, converts to ints."""
    line = read_line()
    if not line:
         sys.stderr.write("Validator Error: Unexpected EOF while reading integer line.\n")
         sys.exit(1)
    try:
        return list(map(int, line.split()))
    except ValueError:
        sys.stderr.write(f"Validator Error: Could not parse integers from line: '{line.strip()}'\n")
        sys.exit(1)

def fail(msg):
    """Prints error message to stderr and exits with code 42 (Wrong Answer)."""
    sys.stderr.write(f"Validation Failed: {msg}\n")
    sys.exit(42) # Standard WA code for validators

# --- Main Validation Logic ---
if __name__ == "__main__":
    # 1. Read Problem Input
    try:
        n_line = read_ints()
        if len(n_line) != 2:
            fail(f"Input Error: First line should have 2 integers (n, t), got {len(n_line)}.")
        n, t = n_line

        if not (1 <= n <= 1000):
            fail(f"Input Constraint Violated: n={n} out of range [1, 1000].")
        if not (1 <= t <= 100000):
             fail(f"Input Constraint Violated: t={t} out of range [1, 100000].")

        l_list = read_ints()
        if len(l_list) != n:
             fail(f"Input Error: Second line should have n={n} integers (l_i), got {len(l_list)}.")

        for i, li in enumerate(l_list):
            if not (1 <= li <= 40000):
                 fail(f"Input Constraint Violated: l_{i+1}={li} out of range [1, 40000].")
            if li % 2 != 0:
                 fail(f"Input Constraint Violated: l_{i+1}={li} is not an even integer.")

    except SystemExit: # Propagate fails from reading helpers
         raise
    except Exception as e:
        sys.stderr.write(f"Validator Error: Exception during input reading: {e}\n")
        sys.exit(1) # Internal validator error

    # 2. Read Solution Output
    try:
        ts_ns_line = read_ints()
        if len(ts_ns_line) != 2:
             fail(f"Output Format Error: First output line should have 2 integers (ts, ns), got {len(ts_ns_line)}.")
        ts_sol, ns_sol = ts_ns_line

        if ts_sol < 0 or ns_sol < 0:
             fail(f"Output Value Error: ts ({ts_sol}) and ns ({ns_sol}) must be non-negative.")

        time_spent_list = read_ints()
        if len(time_spent_list) != n:
             fail(f"Output Format Error: Second output line should have n={n} integers (time_spent_i), got {len(time_spent_list)}.")

        for time_val in time_spent_list:
            if time_val < 0:
                 fail(f"Output Value Error: Individual time spent ({time_val}) cannot be negative.")

    except SystemExit: # Propagate fails from reading helpers
         raise
    except Exception as e:
        sys.stderr.write(f"Validator Error: Exception during solution output reading: {e}\n")
        sys.exit(1) # Internal validator error


    # 3. Validate Solution Logic
    # Check 3.1: Total time ts >= t
    if ts_sol < t:
        fail(f"Rule Violated: Reported total time ts={ts_sol} is less than target t={t}.")

    # Check 3.2: Calculate actual total time and runs from time_spent_list
    calculated_ts = 0
    calculated_ns = 0
    for i in range(n):
        time_spent_i = time_spent_list[i]
        full_time_i = l_list[i]
        half_time_i = full_time_i // 2 # l_i is guaranteed even

        calculated_ts += time_spent_i
        runs_on_trail_i = 0

        if time_spent_i == 0:
            runs_on_trail_i = 0
        elif time_spent_i > 0:
            # First run must be full. Any positive time implies at least one full run occurred.
            if time_spent_i < full_time_i:
                 fail(f"Rule Violated: Trail {i+1} (full time {full_time_i}) has time spent {time_spent_i}, which is positive but less than a full run.")

            # Time spent must be full_time + k * half_time for k >= 0
            remaining_time = time_spent_i - full_time_i
            if remaining_time < 0: # Should be caught above, but double check
                 fail(f"Internal Logic Error: Trail {i+1} remaining time calculation negative.")

            if remaining_time % half_time_i != 0:
                 fail(f"Rule Violated: Trail {i+1} (full {full_time_i}, half {half_time_i}) has time spent {time_spent_i}. The time after the first full run ({remaining_time}) is not a multiple of the half-run time.")

            num_half_runs = remaining_time // half_time_i
            runs_on_trail_i = 1 + num_half_runs # 1 full run + k half runs
        else:
             # Should not happen due to check time_val >= 0 earlier
             fail(f"Internal Logic Error: Negative time_spent_i ({time_spent_i}) encountered for trail {i+1}.")

        calculated_ns += runs_on_trail_i

    # Check 3.3: Verify consistency of reported vs calculated ts
    if calculated_ts != ts_sol:
        fail(f"Consistency Error: Reported ts={ts_sol} does not match sum of individual times spent ({calculated_ts}).")

    # Check 3.4: Verify consistency of reported vs calculated ns
    if calculated_ns != ns_sol:
         fail(f"Consistency Error: Reported ns={ns_sol} does not match calculated number of runs ({calculated_ns}).")

    # If all checks pass, the solution is valid (though not necessarily optimal)
    sys.exit(0) # Exit code 0 for success
