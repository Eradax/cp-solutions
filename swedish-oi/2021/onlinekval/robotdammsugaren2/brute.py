#!/usr/bin/env python3
import time
import random


t_case = int(input())
R, C, N = map(int, input().split())
grid = [input().strip() for _ in range(R)]

start_r, start_c = -1, -1
for r_idx in range(R):
    for c_idx in range(C):
        if grid[r_idx][c_idx] == "O":
            start_r, start_c = r_idx, c_idx
            break
    if start_r != -1:
        break

moves = {"^": (-1, 0), ">": (0, 1), "v": (1, 0), "<": (0, -1)}
move_chars = ["^", ">", "v", "<"]

best = ""
max_vis = -1
start_time = time.time()
time_limit = 11.5

run_count = 0
while time.time() - start_time < time_limit:
    run_count += 1
    curr_r, curr_c = start_r, start_c
    visited = set()
    visited.add((curr_r, curr_c))
    curr = []

    for _ in range(N):
        pos_mv = []

        for move_char in move_chars:
            dr, dc = moves[move_char]
            nr, nc = curr_r + dr, curr_c + dc
            score = -1

            if grid[nr][nc] != "#":
                is_new = (nr, nc) not in visited
                if is_new:
                    freedom = 0
                    for next_dr, next_dc in moves.values():
                        nnr, nnc = nr + next_dr, nc + next_dc
                        if grid[nnr][nnc] != "#" and (nnr, nnc) not in visited:
                            freedom += 1
                    score = (R * C) + freedom
                else:
                    score = 0

            if score > -1:
                pos_mv.append((score, move_char, nr, nc))

        mchoice = None
        actr, actc = (
            curr_r,
            curr_c,
        )

        if not pos_mv:
            mchoice = random.choice(move_chars)
        else:
            pos_mv.sort(key=lambda x: x[0], reverse=True)
            best_score = pos_mv[0][0]
            best_options = [m for m in pos_mv if m[0] == best_score]

            chosen_score, mchoice, actr, actc = random.choice(
                best_options
            )

        curr.append(mchoice)
        curr_r, curr_c = actr, actc
        visited.add((curr_r, curr_c))

    curr_vis = len(visited)
    if curr_vis > max_vis:
        max_vis = curr_vis
        best = "".join(curr)

if not best:
    best = "^" * N

print(best)
