from subprocess import Popen, PIPE
from collections import Counter
n = int(input())

if n == 1:
    print(1)
    exit()

n = str((n * (n + 1)) // 2)

proc = Popen(args=["factor", n], stdout=PIPE)

out, err = proc.communicate()

c = Counter(out.decode().split(": ")[1].strip().split())

ans = 1
for i in c:
    ans *= c[i] + 1

print(ans)
