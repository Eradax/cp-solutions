#!/usr/bin/env python3
import struct
def binary(num):
    return ''.join('{:0>8b}'.format(c) for c in struct.pack('!f', num))

x,y=map(int,input().split())

xb = binary(x)
yb = binary(y)

# print(f"{xb = }")
# print(f"{yb = }")

xe = int(xb[1:9], 2)
ye = int(yb[1:9], 2)

xm = xb[9:]
ym = yb[9:]

whole = ye-xe

# print(f"{whole = }")

ans = 0

ans += max(whole-1,0) * 2**23

if whole == 0:
	ans += int(ym,2)-int(xm,2)-1
else:
	ans += 2**23-1 - int(xm,2)
	# print(f"{2**23-1 - int(xm,2) = }")
	ans += int(ym,2)
	# print(f"{int(ym,2) = }")

print(ans)

