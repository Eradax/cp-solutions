num = int(input())

for i in range(num):
    inp = [*map(int, input().split())]
    n = inp[0]
    cords = [inp[1:][i:i + 2] for i in range(0, len(inp[1:]), 2)]
    
    xcords = [i[0] for i in cords]
    ycords = [i[1] for i in cords]
    sum = 0
    
    for i in range(n):
        sum += xcords[i]*ycords[(i+1)%n] - ycords[i]*xcords[(i+1)%n]
    print(sum/2)

