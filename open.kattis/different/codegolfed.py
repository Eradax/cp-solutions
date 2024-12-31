#!/usr/bin/env python3

import sys
for line in sys.stdin:
    a,b=map(int, line.split())
    print(abs(a-b))
