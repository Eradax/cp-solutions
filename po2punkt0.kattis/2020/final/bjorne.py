n, d = map(int, input().split())

months = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

someone_wakey = [0] * 365

def day():
    a, b = map(int, input().split('/'))
    day = 0
    for i in range(b): day += months[i]
    return (day + a-1 + d)%365



bjarne = day()

for _ in range(n-1): someone_wakey[day()] = 1

last = bjarne
days = 365 - d
ret = 0

while days < 365:
    for i in range(365-d)[::-1]:
        if someone_wakey[(last + i + 1)%365]:
            last = (last + i + 1) % 365
            ret += 1
            days += i + 1
            break
        if i == 0:
            print(-1)
            exit()

print(ret)

