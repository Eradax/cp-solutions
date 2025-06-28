#!/usr/bin/env python3
import subprocess

n = input()
print(subprocess.check_output(["factor", n]).decode().split(':')[1].strip())
