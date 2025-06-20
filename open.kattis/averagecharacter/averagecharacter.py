s = input()
n = len(s)

s = sum(ord(i) for i in s)

print(chr(s // n))
