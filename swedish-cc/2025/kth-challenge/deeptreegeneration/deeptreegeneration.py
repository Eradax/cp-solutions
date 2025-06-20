n = int(input())
vals = [int(i) - 1 for i in input().split()]

nums = [0] * n
for i in vals:
    nums[i] += 1

new = [-1] * n
i = 0
while i < n:
    j = i + 1
    while j < n and nums[j] == 0:
        j += 1
    if j >= n:
        break

    new[j] = i
    nums[i] -= 1
    i = j

j = 0
for i in range(1, n):
    if new[i] != -1:
        continue

    while nums[j] == 0:
        j += 1

    new[i] = j
    nums[j] -= 1

print(*[i + 1 for i in new[1:]])
