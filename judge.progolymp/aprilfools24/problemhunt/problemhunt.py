#!/usr/bin/env python3
try:
	n = int(input())
except Exception:
	print("APRIL{wait...why_1s_ther3_4_flag_h3re}")
	exit()
R = list(map(int, input().split()))
print(min(R)+1)

