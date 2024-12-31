#!/usr/bin/env python3

import math
def main():
	n: int = int(input())

	"""
	Each day we calculate estimated time if we print 3dprinters or statues
	Like a easier version of pickle clicker
	"""

	statues = 0
	printers = 1
	day = 0
	while statues < n:
		day += 1
		if math.ceil((n-statues) / (printers)) > 1 + math.ceil((n-statues) / (2*printers)):
			printers*=2
		else:
			print(day-1+ math.ceil((n-statues) / (printers)))
			exit()
main()