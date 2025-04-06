#!/usr/bin/env python3
import subprocess
import itertools
import sys


def error(msg, gen_data=None, sol_data=None, graph=None, final_state=None):
    sys.stderr.write("Validator error: " + msg + "\n")
    if gen_data is not None:
        sys.stderr.write("=== Generated Input ===\n")
        sys.stderr.write(gen_data + "\n")
    if sol_data is not None:
        sys.stderr.write("=== Candidate Output ===\n")
        sys.stderr.write(sol_data + "\n")
    if graph is not None:
        sys.stderr.write("=== Graph (adjacency list) ===\n")
        for node in sorted(graph.keys()):
            sys.stderr.write(f"{node}: {graph[node]}\n")
    if final_state is not None:
        sys.stderr.write("=== Final simulation state ===\n")
        sys.stderr.write(str(final_state) + "\n")
    sys.exit(1)


def parse_input(data):
    tokens = data.strip().split()
    if len(tokens) < 2:
        error("Input must contain at least two numbers (X and Y).", gen_data=data)
    try:
        X = int(tokens[0])
        Y = int(tokens[1])
    except Exception as e:
        error("Error parsing input: " + str(e), gen_data=data)

    return X, Y


def simulate_bakework(X, N, graph, T=10_000):
    current = [0] * (N + 1)
    current[1] = X
    outdeg = [0] * (N + 1)

    for v in range(1, N + 1):
        outdeg[v] = len(graph.get(v, []))

    for _ in range(T):
        next_state = [0] * (N + 1)
        for v in range(1, N + 1):
            amt = current[v]
            d = outdeg[v]
            if d == 0:
                next_state[v] += amt
            else:
                q = amt // d
                r = amt % d
                next_state[v] += r
                for u in graph[v]:
                    next_state[u] += q

        current = next_state
    return current


def validate_solution(gen_data, sol_data):
    X, Y = parse_input(gen_data)

    candidate_lines = sol_data.strip().splitlines()

    if len(candidate_lines) == 1 and candidate_lines[0].strip() == "-1":
        if X < Y or (X > 1 and Y == 1):
            return True
        else:
            error(
                "Candidate output -1 but instance is solvable (X >= Y and not (X>1 and Y==1)).",
                gen_data=gen_data,
                sol_data=sol_data,
            )

    header = candidate_lines[0].split()
    if len(header) != 2:
        error(
            "First line should contain exactly two integers (N and M).",
            gen_data=gen_data,
            sol_data=sol_data,
        )

    try:
        N = int(header[0])
        M = int(header[1])
    except Exception as e:
        error("Error parsing header: " + str(e), gen_data=gen_data, sol_data=sol_data)

    if N < 2:
        error("N must be at least 2.", gen_data=gen_data, sol_data=sol_data)

    if len(candidate_lines) != 1 + M:
        error(
            f"Expected {M} edge lines, but found {len(candidate_lines) - 1}.",
            gen_data=gen_data,
            sol_data=sol_data,
        )

    graph = {v: [] for v in range(1, N + 1)}
    seen_edges = set()

    for i in range(1, M + 1):
        parts = candidate_lines[i].split()

        if len(parts) != 2:
            error(
                f"Line {i + 1}: Each edge line must have two integers.",
                gen_data=gen_data,
                sol_data=sol_data,
            )

        try:
            u = int(parts[0])
            v = int(parts[1])
        except Exception as e:
            error(
                f"Line {i + 1}: Error parsing edge: {str(e)}",
                gen_data=gen_data,
                sol_data=sol_data,
            )

        if not (1 <= u <= N and 1 <= v <= N):
            error(
                f"Line {i + 1}: Node numbers must be in range 1..N.",
                gen_data=gen_data,
                sol_data=sol_data,
            )

        if u == v:
            error(
                f"Line {i + 1}: Self–loops are not allowed (u cannot equal v).",
                gen_data=gen_data,
                sol_data=sol_data,
            )

        if (u, v) in seen_edges:
            error(
                f"Line {i + 1}: Duplicate edge ({u}, {v}) detected.",
                gen_data=gen_data,
                sol_data=sol_data,
            )

        seen_edges.add((u, v))
        graph[u].append(v)

    for v in range(1, N + 1):
        if len(graph[v]) != len(set(graph[v])):
            error(
                f"Node {v} has duplicate outgoing edges.",
                gen_data=gen_data,
                sol_data=sol_data,
            )

    final_state = simulate_bakework(X, N, graph, T=10_000)
    final_value = final_state[N]

    if final_value != Y:
        error(
            f"After simulation, node {N} has {final_value} ingredients but expected {Y}.",
            gen_data=gen_data,
            sol_data=sol_data,
            graph=graph,
            final_state=final_state,
        )

    return True


gen = "./gen.py"
sol = "./sol.o"

for round in itertools.count(1):
    if round % 100 == 0:
        print(f"{round = }")

    try:
        gen_process = subprocess.run(
            [gen],
            capture_output=True,
            text=True,
            check=True,
        )
    except subprocess.CalledProcessError as e:
        sys.stderr.write("Generator crashed:\n" + e.stdout + "\n" + e.stderr)
        sys.exit(1)

    sol_process = subprocess.run(
        [sol],
        input=gen_process.stdout,
        capture_output=True,
        text=True,
    )

    if sol_process.returncode != 0:
        print(f"{' Sol crashed ': -^72}")
        print(f"{f' after {round} rounds': -^72}")
        print(f"{' Generated Input ': -^72}")
        print(gen_process.stdout)
        break

    try:
        valid = validate_solution(gen_process.stdout, sol_process.stdout)
    except Exception as e:
        print(f"{' Found difference ': -^72}")
        print(f"{f' after {round} rounds': -^72}")
        print(f"{' Generated Input ': -^72}")
        print(gen_process.stdout)
        print(f"{' Candidate Output ': -^72}")
        print(sol_process.stdout)
        print("Exception:", str(e))
        break
