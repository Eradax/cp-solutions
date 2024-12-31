#!/usr/bin/env python3
r, c, n = map(int, input().split())

instructions = [*input()]

# R, C
position = (0, 0)
visited = set()

graph = []
for i in range(r):
    row = [*input()]
    if "O" in row:
        position = (i, row.index("O"))
    graph.append(row)

visited.add(position)

for move in instructions:
    # Down
    if move == "v":
        # print("Down")
        newPos = 0
        for npos in range(position[0], r):
            if graph[npos][position[1]] == "#":
                newPos = npos - 1
                break
            visited.add((npos, position[1]))

        position = (newPos, position[1])

    # Right
    elif move == ">":
        # print("Right")
        newPos = 0
        for npos in range(position[1], c):
            if graph[position[0]][npos] == "#":
                newPos = npos - 1
                break
            visited.add((position[0], npos))

        position = (position[0], newPos)
    # Upp

    elif move == "^":
        # print("Upp")
        newPos = 0
        for npos in range(position[0], -1, -1):
            if graph[npos][position[1]] == "#":
                newPos = npos + 1
                break
            visited.add((npos, position[1]))

        position = (newPos, position[1])

    # Left
    elif move == "<":
        # print("Left")
        newPos = 0
        for npos in range(position[1], -1, -1):
            if graph[position[0]][npos] == "#":
                newPos = npos + 1
                break
            visited.add((position[0], npos))

        position = (position[0], newPos)

    # print(f"New position: {position}")

print(len(visited))
