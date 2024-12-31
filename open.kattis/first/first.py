#!/usr/bin/env python3

t = int(input())

def to_base(number, base):
    if number == 0:
        return "0"

    digits = ""
    while number:
        digits += str(number % base)
        number //= base
    return digits[::-1]

for j in range(1, t+1):
    alien, source, target = input().split()
    
    to10 = dict(zip(source, range(len(source))))
    from10 = dict(zip([str(i) for i in range(len(target))], target))
    
    num = 0
    alien = alien[::-1]
    for i in range(len(alien)):
        num += to10[alien[i]] * (len(source)**i)
        
    num = to_base(num, len(target))
    print(f"Case #{j}: {''.join([from10[x] for x in num])}")